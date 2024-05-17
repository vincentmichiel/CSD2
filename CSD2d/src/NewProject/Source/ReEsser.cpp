/*
  ==============================================================================

    ReEsser.cpp
    Created: 17 May 2024 11:19:37am
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#include "ReEsser.h"

void ReEsser::processSpectrum(float* data, int numBins)
{
    auto* cdata = reinterpret_cast<std::complex<float>*>(data);

    for (int i = 0; i < numBins; ++i) {
        float magnitude = std::abs(cdata[i]);
        float phase = std::arg(cdata[i]);

        // spectral processing
        
        // backwards conversion
        cdata[i] = std::polar(magnitude, phase);
    }
}
