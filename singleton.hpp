#ifndef singleton_hpp___
#define singleton_hpp___

#ifdef TEST_COMPILE
#include "threads.hpp"
#else
#include <gebi/threads.hpp>
#endif

namespace Gebi
{

  /*
  // class Singleton  {{{
  template<class T>
  class Singleton
  {
    private:
      Singleton();
      Singleton(Singleton const &);
      ~Singleton();
      Singleton &operator=(Singleton const &);

    public:
      static T& instance()
      {
        static T obj;
        return obj;
      }
  };
  // }}}
  */

  // possible problems with static object initialisation order
  template<class T>
  struct createMeyers
  {
    static inline T* create()
    {
      static T instance_;
      return &instance_;
    }
  };

  // memleak, T never gets freed
  template<class T>
  struct createGamma
  {
    static inline T* create()
      { return new T; }
  };


  template<class T, template<class> class creationPolicy=createMeyers, class LockType=NullMutex>
  class Singleton
  {
    private:
      Singleton();
      Singleton(Singleton const &);
      ~Singleton();
      Singleton &operator=(Singleton const &);

      static T* instance_;
      static LockType lock_;

    public:
      static T& instance()
      {
        if(!instance_) {
          Guard<LockType, LockMutex> guard(lock_);
          if(!instance_)
            instance_ = creationPolicy<T>::create();
        }
        return *instance_;
      }
  };

  template <class T, template<class> class C, class M>
  T* Singleton<T,C,M>::instance_=0;

} // end namespace Gebi

#endif
// vim:foldmethod=marker
