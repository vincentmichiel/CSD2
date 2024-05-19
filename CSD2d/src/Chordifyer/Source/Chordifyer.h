/*
  ==============================================================================

    Chordifyer.h
    Created: 12 May 2024 12:40:00pm
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#pragma once

#include "FFT.h"

struct Note {
    char root;
    float frequency;
};

class Chordifyer : public FFT {
public:
    using FFT::FFT;
    void prepare();
    ~Chordifyer();
    
private:
    Note notes[7];
    void processSpectrum(float* data) override;
};
