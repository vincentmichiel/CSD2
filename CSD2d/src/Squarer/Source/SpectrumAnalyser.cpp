/*
  ==============================================================================

    SpectrumAnalyser.cpp
    Created: 21 May 2024 9:10:02am
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#include "SpectrumAnalyser.h"

SpectrumAnalyser::~SpectrumAnalyser(){};

void SpectrumAnalyser::processSpectrum(float* data)
{
    auto* cdata = reinterpret_cast<std::complex<float>*>(data);
    
    for (int i = 0; i < numBins; ++i) {
        sidechainFFT[i] = cdata[i];
    }
}
