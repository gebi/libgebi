#ifndef random_hpp___
#define random_hpp___

#ifdef TEST_COMPILE
#include "singleton.hpp"
#else
#include <gebi/singleton.hpp>
#endif

namespace gebi
{

namespace probability
{

class RandomGenerator
{ 
public:
    RandomGenerator() throw() {}
    ~RandomGenerator() throw() {}

    void init() { srand((unsigned)time( NULL )); }
    void randomize() { srand((unsigned int)rand()); }
    template<unsigned int max_int>
    unsigned int getUpTo()
    { 
        double tmp = (double)rand() / RAND_MAX;
        return((unsigned int)(tmp * max_int + 1));
    }
};
typedef Singleton<RandomGenerator, createMeyers, NullMutex> Random;

template<typename T, typename output_t>
output_t calcAverage(T &array)
{
    return accumulate(array.begin(), array.end(), output_t(0)) / array.size();
}

template<typename T, typename output_t>
output_t calcStandardDeviation(T &array, output_t middle_value)
{
    output_t deviation = output_t();
    output_t tmp_abw;
    typename T::const_iterator i;
    typename T::size_type size = array.size();
    for (i = array.begin(); i != array.end(); i++)
    {
        tmp_abw = *i - middle_value;
        deviation += tmp_abw * tmp_abw / size;
    }
        return sqrt(deviation);
}

} // end namespace probability

} // end namespace gebi

// vim:foldmethod=marker
#endif
