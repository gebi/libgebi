#include "invsqrt_priv.h"
#include "invsqrt.h"

namespace gebi
{

float invsqrt(float x) { return invsqrt_helper<float>(x); }
double invsqrt(double x) { return invsqrt_helper<double>(x); }

}
