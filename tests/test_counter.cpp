#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/auto_unit_test.hpp>

#include "counter.hpp"
using namespace gebi;


// default
BOOST_AUTO_TEST_CASE(CounterCTorTestDefault)
{
    Counter<long, NullMutex> cntr;
    BOOST_CHECK_EQUAL(cntr.get(), 0l);
}

// initialised with long
BOOST_AUTO_TEST_CASE(CounterCTorTestInitLong)
{
    Counter<long, NullMutex> cntr(5);
    BOOST_CHECK_EQUAL(cntr.get(), 5l);
}

// initialised with another counter
BOOST_AUTO_TEST_CASE(CounterCTorTestInitCntr)
{
    Counter<long, NullMutex> cntr(4);
    Counter<long, NullMutex> cntr1(cntr);
    BOOST_CHECK_EQUAL(cntr1.get(), 4l);
}

// operator=
BOOST_AUTO_TEST_CASE(CounterOperatorAssignmentTest)
{
    Counter<long, NullMutex> cntr(4);
    Counter<long, NullMutex> cntr1(6);
    cntr = cntr1;
    BOOST_CHECK_EQUAL(cntr.get(), 6l);
}

// operator--
BOOST_AUTO_TEST_CASE(CounterOperatorDecTest)
{
    Counter<long, NullMutex> cntr(4);
    --cntr;
    BOOST_CHECK_EQUAL(cntr.get(), 3l);
}

// operator++
BOOST_AUTO_TEST_CASE(CounterOperatorIncTest)
{
    Counter<long, NullMutex> cntr(4);
    ++cntr;
    BOOST_CHECK_EQUAL(cntr.get(), 5l);
}
