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
    void setThreshHold(float threshHold);
    void setCenterFrequency(float frequency);
    void setBandWidth(float bandWidth);
    
private:
    float threshHold = 0.01;
    float target;
    float bandWidth;
    void processSpectrum(float* data) override;
};
