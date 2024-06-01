/*
  ==============================================================================

    SpectrumAnalyser.h
    Created: 21 May 2024 9:10:02am
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#pragma once
#include "FFT.h"

class SpectrumAnalyser : public FFT {
public:
    using FFT::FFT;
    ~SpectrumAnalyser();
    std::array<std::complex<float>, numBins> sidechainFFT;
    
private:
    void processSpectrum(float* data) override;
};
