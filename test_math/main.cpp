#include "math.hpp"
using namespace gebi;

#include <cmath>
#include <iostream>
#include <string>
#include <loki/Factory.h>
using namespace std;

#include <unistd.h>

int main()
{
    cout <<Sin<1,2,double>::value() <<" " <<sin(1) <<endl;
    cout <<Cos<1,2,double>::value() <<" " <<cos(1) <<endl;
    return 0;
}
