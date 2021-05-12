#include <boost/test/unit_test.hpp>

#include <math.hpp>
using namespace gebi;


BOOST_AUTO_TEST_CASE(SinTest)
{
    float sinf = Sin<32,5,float>::value();
    double sind = Sin<32,5,double>::value();
    BOOST_CHECK_EQUAL(sinf, 0.471396744f);
    BOOST_CHECK_EQUAL(sind, 0.47139673682599764);
}
