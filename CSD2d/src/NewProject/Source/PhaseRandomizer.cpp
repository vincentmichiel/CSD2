/*
  ==============================================================================

    PhaseRandomizer.cpp
    Created: 12 May 2024 3:06:35pm
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#include "PhaseRandomizer.h"
#include "Interpolate.h"

PhaseRandomizer::~PhaseRandomizer(){};

void PhaseRandomizer::processSpectrum(float* data)
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
