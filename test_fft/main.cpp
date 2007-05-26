#include "fft.hpp"
using namespace gebi;

#include <iostream>
#include <string>
#include <loki/Factory.h>
using namespace std;

#include <unistd.h>

int main()
{
    Loki::Factory<AbstractFFT<double>,unsigned int> gfft_factory;
    FactoryInit<GFFTList<GFFT,10,27>::Result>::apply(gfft_factory);
    AbstractFFT<double>* gfft = gfft_factory.CreateObject(26);

    return 0;
}
