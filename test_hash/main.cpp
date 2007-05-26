#include "hash.hpp"
using namespace gebi;

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

#include <unistd.h>

int main()
{
    const char arr[] = "abcdefg";

    unsigned tmp = gebi::qedhash(arr, sizeof(arr));
    cout <<tmp <<endl;

    return 0;
}
