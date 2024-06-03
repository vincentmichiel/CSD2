/*
  ==============================================================================

    Chordifyer.cpp
    Created: 19 May 2024 12:40:00pm
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#include "Chordifyer.h"

Chordifyer::~Chordifyer(){};

void Chordifyer::setSidechainGain(float gain){
    if(gain > 0){
        sidechainGain = 1 * (1 + gain / 3.0f);
    } else if (gain < 0){
        sidechainGain = 1 / (1 + abs(gain) / 3.0f);
    } else {
        sidechainGain = 1;
    }
}

void Chordifyer::processSpectrum(float* data)
{
    auto* cdata = reinterpret_cast<std::complex<float>*>(data);
    
    for (int i = 0; i < numBins; ++i) {
        float magnitude = std::abs(cdata[i]);
        float phase = std::arg(cdata[i]);
        
        magnitude *= std::abs(sidechainAnalyser.sidechainFFT[i] * sidechainGain);
        
        // backwards conversion
        cdata[i] = std::polar(magnitude, phase);
    }
}
