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

class Resonator : public FFT {
public:
    using FFT::FFT;
    void prepare(float frequency, float depth, double samplerate);
    Sine * lfo;
    SpectrumAnalyser spectrumAnalyser;
    ~Resonator();
    void setDepth(float depth);
    
private:
    float frequency;
    float depth;
    void processSpectrum(float* data) override;
};
