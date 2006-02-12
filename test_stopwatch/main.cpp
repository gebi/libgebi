#include "stopwatch.hpp"
using namespace gebi;

#include <iostream>
#include <string>
using namespace std;

#include <unistd.h>

int main()
{
    {
        Stopwatch<CoutNotifier> sw;
        sleep(1);
    }
    cout <<endl;

    {
        Stopwatch<> sw;
        sleep(1);
        cout << sw.stop() <<endl;
    }

    return 0;
}
