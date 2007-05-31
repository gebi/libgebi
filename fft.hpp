#ifndef ___fft_hpp___
#define ___fft_hpp___

#include <math.hpp>

#include <loki/Typelist.h>

// license: public domain?
// FFT implementation from:
// http://www.ddj.com/dept/cpp/199500857
// http://www.ddj.com/dept/cpp/199702312

namespace gebi
{

template<typename T>
void scramble(T* data, unsigned nn)
{
    // reverse-binary reindexing
    unsigned i, j, m, n;
    n = nn<<1;
    j=1;
    for (i=1; i<n; i+=2) {
        if (j>i) {
            swap(data[j-1], data[i-1]);
            swap(data[j], data[i]);
        }
        m = nn;
        while (m>=2 && j>m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    }
}

template<unsigned N, typename T = double>
class DanielsonLanczos {
   DanielsonLanczos<N/2,T> next;
public:
   void apply(T* data) {
      next.apply(data);
      next.apply(data+N);


      T wtemp,tempr,tempi,wr,wi,wpr,wpi;
      //wtemp = sin(M_PI/N);
      wtemp = -Sin<N,1,T>::value();
      wpr = -2.0*wtemp*wtemp;
      //wpi = -sin(2*M_PI/N);
      wpi = -Sin<N,2,T>::value();
      wr = 1.0;
      wi = 0.0;
      for (unsigned i=0; i<N; i+=2) {
        tempr = data[i+N]*wr - data[i+N+1]*wi;
        tempi = data[i+N]*wi + data[i+N+1]*wr;
        data[i+N] = data[i]-tempr;
        data[i+N+1] = data[i+1]-tempi;
        data[i] += tempr;
        data[i+1] += tempi;


        wtemp = wr;
        wr += wr*wpr - wi*wpi;
        wi += wi*wpr + wtemp*wpi;
      }
   }
};

// DanielsonLanczos<4,T> and DanielsonLanczos<2,T> {{{
template<typename T>
class DanielsonLanczos<4,T> {
public:
   void apply(T* data) {
      T tr = data[2];
      T ti = data[3];
      data[2] = data[0]-tr;
      data[3] = data[1]-ti;
      data[0] += tr;
      data[1] += ti;
      tr = data[6];
      ti = data[7];
      data[6] = data[5]-ti;
      data[7] = tr-data[4];
      data[4] += tr;
      data[5] += ti;

      tr = data[4];
      ti = data[5];
      data[4] = data[0]-tr;
      data[5] = data[1]-ti;
      data[0] += tr;
      data[1] += ti;
      tr = data[6];
      ti = data[7];
      data[6] = data[2]-tr;
      data[7] = data[3]-ti;
      data[2] += tr;
      data[3] += ti;
   }
};


template<typename T>
class DanielsonLanczos<2,T> {
public:
   void apply(T* data) {
      T tr = data[2];
      T ti = data[3];
      data[2] = data[0]-tr;
      data[3] = data[1]-ti;
      data[0] += tr;
      data[1] += ti;
   }
};
// }}}

template<typename T>
class DanielsonLanczos<1,T> {
public:
   void apply(T* data) { }
};


template<typename T>
class AbstractFFT {
public:
   virtual ~AbstractFFT() {}
   virtual void fft(T*) = 0;
};

class EmptyFFT { };

template<unsigned P, typename T = double,
class FactoryPolicy = EmptyFFT>
class GFFT:public FactoryPolicy {
   enum { N = 1<<P };
   DanielsonLanczos<N,T> recursion;
public:
   enum { id = P };
   static FactoryPolicy* Create() {
       return new GFFT<P,T,FactoryPolicy>();
   }
   void fft(T* data) {
      scramble<T>(data,N);
      recursion.apply(data);
   }
};


template<class TList>
struct FactoryInit;

template<class H, class T>
struct FactoryInit<Loki::Typelist<H,T> > {
   template<class Fact>
   static void apply(Fact& f) {
      f.Register(H::id,H::Create);
      FactoryInit<T>::apply(f);
   }
};

template<>
struct FactoryInit<Loki::NullType> {
   template<class Fact>
   static void apply(Fact&) { }
};

template<
template<unsigned,class,class> class FFT,
unsigned Begin, unsigned End,
typename T=double,
class FactoryPolicy=AbstractFFT<T> >
struct GFFTList {
   typedef Loki::Typelist<FFT<Begin,T,FactoryPolicy>,
           typename GFFTList<FFT,Begin+1,End,T,
                    FactoryPolicy>::Result> Result;
};

template<
template<unsigned,class,class> class FFT,
unsigned End, typename T, class FactoryPolicy>
struct GFFTList<FFT,End,End,T,FactoryPolicy> {
   typedef Loki::NullType Result;
};

}; // end namespace gebi

#endif // ___fft_hpp___
