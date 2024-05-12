/*
  ==============================================================================

    PhaseRandomizer.h
    Created: 12 May 2024 3:06:35pm
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#pragma once

#include "FFT.h"

class PhaseRandomizer : public FFT {
public:
    using FFT::FFT;
    ~PhaseRandomizer();
    
private:
    void processSpectrum(float* data, int numBins) override;
};
