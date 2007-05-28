#include "math.hpp"
using namespace gebi;

#include <cmath>
#include <iostream>
#include <string>
using namespace std;

#include <unistd.h>

int main()
{
    cout <<Sin<1,2,double>::value() <<" " <<sin(1) <<endl;
    cout <<Cos<1,2,double>::value() <<" " <<cos(1) <<endl;
    cout <<invsqrt<float>(1.5) <<endl;
    cout <<invsqrt<double>(1.5) <<endl;
    return 0;
}
