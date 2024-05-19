/*
  ==============================================================================

    SidechainAnalyser.h
    Created: 19 May 2024 9:38:56pm
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#pragma once
#include "FFT.h"

class SidechainAnalyser : public FFT {
public:
    using FFT::FFT;
    ~SidechainAnalyser();
    std::array<std::complex<float>, numBins> sidechainFFT;
    
private:
    void processSpectrum(float* data) override;
};
