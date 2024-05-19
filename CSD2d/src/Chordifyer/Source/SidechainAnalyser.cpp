/*
  ==============================================================================

    SidechainAnalyser.cpp
    Created: 19 May 2024 9:38:56pm
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#include "SidechainAnalyser.h"

SidechainAnalyser::~SidechainAnalyser(){};

void SidechainAnalyser::processSpectrum(float* data)
{
    auto* cdata = reinterpret_cast<std::complex<float>*>(data);
    
    for (int i = 0; i < numBins; ++i) {
        sidechainFFT[i] = cdata[i];
    }
}
