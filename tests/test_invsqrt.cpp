#include <boost/test/unit_test.hpp>

#include <invsqrt.h>
using namespace gebi;


BOOST_AUTO_TEST_CASE(InvSqrtFloatTest)
{
    float invsqrt_float = invsqrt(1.5f);
    if( ! (invsqrt_float <= 0.815361918f &&
           invsqrt_float >= 0.815361856f)) {
        BOOST_CHECK_EQUAL(invsqrt_float, 0.815361918);
        BOOST_CHECK_EQUAL(invsqrt_float, 0.815361856);
    }
}

BOOST_AUTO_TEST_CASE(InvSqrtDoubleTest)
{
    double invsqrt_double = invsqrt((double)1.5);
    if( ! (invsqrt_double <= 0.81534821186704776L &&
           invsqrt_double >= 0.81534821186704764L)) {
        BOOST_CHECK_EQUAL(invsqrt_double, 0.81534821186704776);
        BOOST_CHECK_EQUAL(invsqrt_double, 0.81534821186704764);

    }
}
