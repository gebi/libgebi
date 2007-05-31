//#include "invsqrt_priv.h"
#include "invsqrt.h"

namespace gebi
{

// invsqrt from Q3 source with better magic from
// http://www.lomont.org/Math/Papers/2003/InvSqrt.pdf
//
// inline float invsqrt_helper(float x)
// {   
//     float xhalf = 0.5f*x;
//     int i = *(int*)&x;           // get bits for floating value
//     i = 0x5f375a86 - (i>>1);     // gives initial guess y0
//     x = *(float*)&i;             // convert bits back to float
//     x = x*(1.5f-xhalf*x*x);      // Newton step, repeating increases accuracy
//     return x;
// }

#define invsqrt_helper(ftype, itype, magic) \
ftype invsqrt(ftype x) \
{ \
    ftype xhalf = 0.5f*x; \
    itype i = *(itype*)&x; \
    i = magic - (i>>1); \
    x = *(ftype*)&i; \
    x = x*(1.5f-xhalf*x*x); \
    return x; \
}

invsqrt_helper(float, int, 0x5f375a86);
invsqrt_helper(double, long, 0x5fe6ec85e7de30da);

//#undef invsqrt_helper

}
