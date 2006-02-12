#include "counter.hpp"
#include "threads.hpp"

#include <iostream>
using std::cout;
using std::endl;


#ifdef _MT_SUPPORT_
typedef Gebi::Counter<unsigned, Gebi::RWMutex> COUNTER;
#else
typedef Gebi::Counter<unsigned, Gebi::NullMutex> COUNTER;
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
