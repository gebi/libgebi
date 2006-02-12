#include "threads.hpp"
using namespace gebi;

#include <iostream>
using std::cout;
using std::endl;


template<class CounterType, class SimpleLock>
class Counter
{
  private:
    CounterType i_;
    mutable SimpleLock lock_;
    typedef Guard<SimpleLock> MyGuard;

    Counter(Counter &src) {}
    CounterType operator=(Counter &src) {}

  public:
    Counter() : i_(0) {}
    Counter(CounterType i) : i_(i) {}
    ~Counter() {}

    CounterType operator--()
    {
      MyGuard guard(lock_);
      return --i_;
    }

    CounterType operator++()
    {
      MyGuard guard(lock_);
      return ++i_;
    }

    CounterType get() const
    {
      MyGuard guard(lock_);
      return i_;
    }
};


#ifdef _MT_SUPPORT_
typedef Counter<unsigned, ThreadMutex> COUNTER;
#else
typedef Counter<unsigned, NullMutex> COUNTER;
#endif


int main()
{
  COUNTER i;
  unsigned cnt;

  cout << i.get() << endl;
  for(cnt = 0; cnt < 100000000; cnt++)
    ++i;
  cout << i.get() << endl;

  return 0;
}
