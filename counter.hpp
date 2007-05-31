#ifndef ___counter_hpp___
#define ___counter_hpp___

#include <threads.hpp>

namespace gebi
{

  // class Counter  {{{
  template<class CounterType, class RWLockType = NullMutex>
  class Counter
  {
    private:
      CounterType i_;
      mutable RWLockType lock_;
      typedef Guard<RWLockType, LockRead> GuardR;
      typedef Guard<RWLockType, LockWrite> GuardW;


    public:
      Counter() : i_(0) {}
      Counter(const CounterType &i) : i_(i) {}
      Counter(const Counter &src)
      {
        GuardR guard(src.lock_);
        i_ = src.i_;
      }
      Counter &operator=(const Counter &src)
      {
        if(this == &src)
          return *this;
        // Allways aquire the two locks in the SAME ORDER!! (eg. by their address)
        if(&lock_ < &src.lock_) {
          GuardW guard1(lock_);
          GuardR guard2(src.lock_);
        } else {
          GuardR guard2(src.lock_);
          GuardW guard1(lock_);
        }
        // hmm... how do you want it? fast and 'big' or small and slower?
        // GuardW guard1(&lock_ < &src.lock_ ? lock_ : &src.lock_);
        // GuardW guard2(&lock_ > &src.lock_ ? lock_ : &src.lock_);
        i_ = src.i_;
        return *this;
      }
      ~Counter() {}

      CounterType operator-- ()
      {
        GuardW guard(lock_);
        return --i_;
      }
      CounterType operator++ ()
      {
        GuardW guard(lock_);
        return ++i_;
      }

      CounterType get() const
      {
        GuardR guard(lock_);
        return i_;
      }
  }; // }}}

} // namespace gebi

// vim:foldmethod=marker
#endif
