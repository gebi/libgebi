#include <boost/test/auto_unit_test.hpp>

#include <invsqrt.h>
using namespace gebi;

#include <cmath>
#include <iostream>
#include <string>
using namespace std;

#include <unistd.h>

BOOST_AUTO_TEST_CASE(InvSqrtTest)
{   
    float invsqrt_float = invsqrt(1.5f);
    double invsqrt_double = invsqrt((double)1.5);
    BOOST_CHECK_MESSAGE(invsqrt_float == 0.815361917f || 
                        invsqrt_float == 0.815361857f, invsqrt_float);
    BOOST_CHECK_MESSAGE(invsqrt_double == 0.81534821186704765 ||
                        invsqrt_double == 0.81534821186704765, invsqrt_double);
}
