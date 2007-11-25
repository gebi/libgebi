#include <boost/test/auto_unit_test.hpp>
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;

#include <string>
#include <map>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::multimap;
using std::string;
using std::pair;
using std::vector;

#include <hash.hpp>
using namespace gebi;


BOOST_AUTO_TEST_CASE(HashTestA)
{
    BOOST_CHECK_EQUAL(qedhash("a", 2), 3609622876);
    BOOST_CHECK_EQUAL(qedhash("aa", 3), 1644587088);
    BOOST_CHECK_EQUAL(qedhash("aaa", 4), 3474505875);
    BOOST_CHECK_EQUAL(qedhash("aaaa", 5), 3482056723);
    BOOST_CHECK_EQUAL(qedhash("aaaaa", 6), 4066557768);
    BOOST_CHECK_EQUAL(qedhash("aaaaaa", 7), 3407651169);
}

BOOST_AUTO_TEST_CASE(HashTestB)
{
    BOOST_CHECK_EQUAL(qedhash("b", 2), 3880028604);
    BOOST_CHECK_EQUAL(qedhash("bb", 3), 2134675310);
    BOOST_CHECK_EQUAL(qedhash("bbb", 4), 1044646078);
    BOOST_CHECK_EQUAL(qedhash("bbbb", 5), 2882507253);
    BOOST_CHECK_EQUAL(qedhash("bbbbb", 6), 235466585);
    BOOST_CHECK_EQUAL(qedhash("bbbbbb", 7), 940864181);
}

BOOST_AUTO_TEST_CASE(HashTestRandom)
{   
    BOOST_CHECK_EQUAL(qedhash("pG5OSRlkPkDRrgyr", 13), 2235563499);
    BOOST_CHECK_EQUAL(qedhash("BwxHq94NB77GwllN", 13), 1842200859);
    BOOST_CHECK_EQUAL(qedhash("jGT2O760uh9OY0mM", 13), 1513127197);
    BOOST_CHECK_EQUAL(qedhash("qOFDpi+zy23JLOvE", 13), 3392433287);
    BOOST_CHECK_EQUAL(qedhash("stPtVo03WJEmzcow", 13), 240421858);
    BOOST_CHECK_EQUAL(qedhash("7j/ctrLODyyxERPU", 13), 3789180684);
    BOOST_CHECK_EQUAL(qedhash("14838", 6), 2232062922);
    BOOST_CHECK_EQUAL(qedhash("94820", 6), 2232062922);
    BOOST_CHECK_EQUAL(qedhash("8972020", 7), 4294935889);
    BOOST_CHECK_EQUAL(qedhash("8503750", 7), 4294950382);
    BOOST_CHECK_EQUAL(qedhash("8504762", 7), 4294950382);
    BOOST_CHECK_EQUAL(qedhash("8507798", 7), 4294950382);
    BOOST_CHECK_EQUAL(qedhash("8517618", 7), 4294950382);
}

BOOST_AUTO_TEST_CASE(HashTestUniform)
{
    typedef multimap<unsigned, int> m_t;
    typedef pair<unsigned, int> mpair_t;

    m_t m;
    // collisions start at 92000 :/
    for(int i=0; i<90000; ++i) {
        string str = lexical_cast<string>(i);
        unsigned h = qedhash(str.c_str(), str.size());
        m.insert(mpair_t(h, i));
    }

    typedef vector<unsigned> v_t;
    unsigned col = 0; // number of collisions
    unsigned tmp = 0; // previous value
    v_t tmpv;         // values which lead to the collision
    tmpv.reserve(8);
    for(m_t::iterator i = m.begin(); i!=m.end(); ++i) {
        if(tmp == i->first) {
            ++col;
            tmpv.push_back(i->second);
            continue;
        } else if(tmpv.size() >1) {
            cout <<"Collision warning: " <<tmp <<" has " <<tmpv.size() <<" collision(s) ";
            copy(tmpv.begin(), tmpv.end(), std::ostream_iterator<v_t::value_type>(cout, ", "));
            cout <<endl;
            tmpv.clear();
        }
        tmp = i->first;
        tmpv[0] = i->second;
    }
    BOOST_CHECK_EQUAL(col, 0);
}

