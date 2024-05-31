/*
  ==============================================================================

    Squarer.h
    Created: 21 May 2024 8:58:02am
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#pragma once
#include "FFT.h"
#include "Oscillator.hpp"
#include "SpectrumAnalyser.h"

class Squarer : public FFT {
public:
    using FFT::FFT;
    void prepare(float frequency, float depth, double samplerate);
    Block * lfo;
    SpectrumAnalyser spectrumAnalyser;
    ~Squarer();
    void setDepth(float depth);
    
private:
    float frequency;
    float depth;
    void processSpectrum(float* data) override;
};
