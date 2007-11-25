#include "hash.hpp"
using namespace gebi;

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

#include <unistd.h>

int main()
{
    for(;;) {
        string in;
        cout <<"> ";
        cin >>in;
        cout <<qedhash(in.c_str(), in.size()) <<endl;
    }
    return 0;
}
