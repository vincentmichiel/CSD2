/*
  ==============================================================================

    ReEsser.h
    Created: 17 May 2024 11:19:37am
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#pragma once
#include "FFT.h"

class ReEsser : public FFT {
public:
    using FFT::FFT;
    ~ReEsser();
    
private:
    void processSpectrum(float* data, int numBins) override;
};
