#ifndef ___invsqrt_priv_h___
#define ___invsqrt_priv_h___

// type helper for invsqrt
template<typename T>
struct sqrth{};
template<>
struct sqrth<float>{
    typedef int type;
    const static type magic = 0x5f375a86;
};
template<>
struct sqrth<double>{
    typedef long type;
    const static type magic = 0x5fe6ec85e7de30da;
};

// invsqrt from Q3 source with better magic from
// http://www.lomont.org/Math/Papers/2003/InvSqrt.pdf
template<typename T>
inline T invsqrt_helper(T x)
{   
    volatile T xhalf = 0.5f*x;
    typedef typename sqrth<T>::type type;
    volatile type i = *(type*)&x;           // get bits for floating value
    i = sqrth<T>::magic - (i>>1);           // gives initial guess y0
    x = *(T*)&i;                            // convert bits back to float
    x = x*(1.5f-xhalf*x*x);                 // Newton step, repeating increases accuracy
    return x;
}

#endif // ___invsqrt_priv_h___
