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

void Chordifyer::prepare(){
    notes[0].root = 'c';
    notes[1].root = 'd';
    notes[2].root = 'e';
    notes[3].root = 'f';
    notes[4].root = 'g';
    notes[5].root = 'a';
    notes[6].root = 'b';
    
    notes[0].frequency = 32.7;
    notes[1].frequency = 36.71;
    notes[2].frequency = 41.2;
    notes[3].frequency = 43.65;
    notes[4].frequency = 49.0;
    notes[5].frequency = 55.00;
    notes[6].frequency = 61.74;
}

void Chordifyer::processSpectrum(float* data)
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
