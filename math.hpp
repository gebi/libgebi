#ifndef ___math_hpp___
#define ___math_hpp___

namespace gebi
{

const long double M_PI = 3.1415926535897931;

// compiletime Sin / Cos implementations {{{
// license: public domain?
// http://www.ddj.com/dept/cpp/199500857

template<unsigned M, unsigned N, unsigned B, unsigned A>
struct SinCosSeries {
   static double value() {
      return 1-(A*M_PI/B)*(A*M_PI/B)/M/(M+1)
               *SinCosSeries<M+2,N,B,A>::value();
   }
};

template<unsigned N, unsigned B, unsigned A>
struct SinCosSeries<N,N,B,A> {
   static double value() { return 1.; }
};

template<unsigned B, unsigned A, typename T = double>
struct Sin;


template<unsigned B, unsigned A>
struct Sin<B,A,float> {
   static float value() {
      return (A*M_PI/B)*SinCosSeries<2,24,B,A>::value();
   }
};
template<unsigned B, unsigned A>
struct Sin<B,A,double> {
   static double value() {
      return (A*M_PI/B)*SinCosSeries<2,34,B,A>::value();
   }
};

template<unsigned B, unsigned A, typename T = double>
struct Cos;


template<unsigned B, unsigned A>
struct Cos<B,A,float> {
   static float value() {
      return SinCosSeries<1,23,B,A>::value();
   }
};
template<unsigned B, unsigned A>
struct Cos<B,A,double> {
   static double value() {
      return SinCosSeries<1,33,B,A>::value();
   }
};
// }}}

namespace math_
{
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
}

// float invsqrt(float x) {{{
// invsqrt from Q3 source with better magic from
// http://www.lomont.org/Math/Papers/2003/InvSqrt.pdf
template<typename T>
T invsqrt(T x)
{
    volatile T xhalf = 0.5f*x;
    typedef typename math_::sqrth<T>::type type;
    volatile type i = *(type*)&x;           // get bits for floating value
    i = math_::sqrth<T>::magic - (i>>1);   // gives initial guess y0
    x = *(T*)&i;                            // convert bits back to float
    x = x*(1.5f-xhalf*x*x);                 // Newton step, repeating increases accuracy
    return x;
}
// }}}

} // end namespace gebi

#endif // ___math_hpp___
