//Copyright (c) 2019 Mauricio Kugler, Nagoya Institute of Technology

#include "FastFourierTransform.h"
#include <stdlib.h>
#include <iostream>

int main()
{
    const unsigned int n1 = 1024;

    float *x = new float[n1];
    for(unsigned int i=0;i<n1;i++) {
        x[i] = ((float)rand()/RAND_MAX)*2-1;
    }

    FastFourierTransform FFT = FastFourierTransform(n1);

    complex<float> *y = FFT.fft1(x);
    float *z = FFT.ifft1(y);
    
    for(int i = 0; i < n1; i++){
        std::cout << y[i] << '\n';
    }
    
    return 0;
}
