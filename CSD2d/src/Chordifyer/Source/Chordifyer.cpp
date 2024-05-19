/*
  ==============================================================================

    Chordifyer.cpp
    Created: 19 May 2024 12:40:00pm
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#include "Chordifyer.h"
#include "Interpolate.h"

Chordifyer::~Chordifyer(){};

void Chordifyer::processSpectrum(float* data)
{
    auto* cdata = reinterpret_cast<std::complex<float>*>(data);

    for (int i = 0; i < numBins; ++i) {
        float magnitude = std::abs(cdata[i]);
        float phase = std::arg(cdata[i]);

        // spectral processing
        // random phase
        phase *= float(i);
        
        // lowpass
        if(i > 20){
            magnitude *= 0.01;
        }
        
        // backwards conversion
        cdata[i] = std::polar(magnitude, phase);
    }
}
