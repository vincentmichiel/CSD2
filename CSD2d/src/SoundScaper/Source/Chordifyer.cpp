/*
  ==============================================================================

    Chordifyer.cpp
    Created: 19 May 2024 12:40:00pm
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#include "Chordifyer.h"

Chordifyer::~Chordifyer(){};

void Chordifyer::processSpectrum(float* data)
{
    auto* cdata = reinterpret_cast<std::complex<float>*>(data);
    
    for (int i = 0; i < numBins; ++i) {
        float magnitude = std::abs(cdata[i]);
        float phase = std::arg(cdata[i]);
        
        magnitude *= std::abs(sidechainAnalyser.sidechainFFT[i]);
        
        // backwards conversion
        cdata[i] = std::polar(magnitude, phase);
    }
}
