#include "invsqrt.h"
using namespace gebi;

#include <cmath>
#include <iostream>
#include <string>
using namespace std;

#include <unistd.h>

int main()
{
    cout <<invsqrt(1.5f) <<endl;
    cerr <<invsqrt((double)1.5) <<endl;
    return EXIT_SUCCESS;
}
