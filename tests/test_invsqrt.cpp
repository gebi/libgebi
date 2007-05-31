#include <boost/test/auto_unit_test.hpp>

#include "invsqrt.h"
using namespace gebi;

#include <cmath>
#include <iostream>
#include <string>
using namespace std;

#include <unistd.h>

BOOST_AUTO_TEST_CASE(InvSqrtTest)
{   
    BOOST_CHECK_EQUAL(invsqrt(1.5f), 0.815361917f);
    BOOST_CHECK_EQUAL(invsqrt((double)1.5), (double)0.81534821186704765);
}
