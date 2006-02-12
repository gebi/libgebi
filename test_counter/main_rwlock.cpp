#include "counter.hpp"
#include "threads.hpp"

#include <iostream>
using std::cout;
using std::endl;


#ifdef _MT_SUPPORT_
typedef gebi::Counter<unsigned, gebi::RWMutex> COUNTER;
#else
typedef gebi::Counter<unsigned, gebi::NullMutex> COUNTER;
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
