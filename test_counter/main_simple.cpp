#include <iostream>

using namespace std;

int main()
{
  unsigned cnt, i(0);

  for(cnt = 0; cnt < 100000000; cnt++)
    ++i;
  cout << i << endl;
  return 0;
}
