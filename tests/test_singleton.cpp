#include <boost/test/auto_unit_test.hpp>

#include <singleton.hpp>
using namespace gebi;

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

struct Test
{
    static int num_;
    int i_;

    Test() : i_(0) { ++num_; }
    ~Test() { i_=-1; }
    void set(int i) { i_ = i; }
private:
    Test(const Test &);
    Test& operator=(Test const &);
};
int Test::num_ = 0;

BOOST_AUTO_TEST_CASE(SingletonMeyers)
{
    typedef Singleton<Test, createMeyers> S;

    Test* tmp = S::instance();
    tmp->set(5);
    BOOST_CHECK_EQUAL(tmp->i_, S::instance()->i_);

    S::instance()->set(3);
    BOOST_CHECK_EQUAL(tmp->i_, 3);
    BOOST_CHECK_EQUAL(S::instance()->i_, 3);

    BOOST_CHECK_EQUAL(tmp->num_, 1);
    tmp->num_ = 0;
}

BOOST_AUTO_TEST_CASE(SingletonGamma)
{
    typedef Singleton<Test, createGamma> S;

    Test* tmp = S::instance();
    tmp->set(5);
    BOOST_CHECK_EQUAL(tmp->i_, S::instance()->i_);

    S::instance()->set(3);
    BOOST_CHECK_EQUAL(tmp->i_, 3);
    BOOST_CHECK_EQUAL(S::instance()->i_, 3);

    BOOST_CHECK_EQUAL(tmp->num_, 1);
    tmp->num_ = 0;
}

