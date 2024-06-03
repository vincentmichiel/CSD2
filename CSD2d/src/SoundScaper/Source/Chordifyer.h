/*
  ==============================================================================

    Chordifyer.h
    Created: 12 May 2024 12:40:00pm
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#pragma once

#include "FFT.h"
#include "SpectrumAnalyser.h"

class Chordifyer : public FFT {
public:
    using FFT::FFT;
    ~Chordifyer();
    SpectrumAnalyser sidechainAnalyser;
    void setSidechainGain(float gain);
    
private:
    void processSpectrum(float* data) override;
    float sidechainGain;
};
