//
//  Synth.hpp
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 17/12/2023.
//

#ifndef Synth_hpp
#define Synth_hpp

#include <stdio.h>
#include <vector>
#include "Oscillator.hpp"

class Synth {
private:
    float sampleRate;
    double amp;
    float phase;
    int voices;
    // array of oscillators
    std::vector<std::unique_ptr<Oscillator>> oscillators;
    double midiNoteToFrequency(int midiNote);
    
public:
    // constructor destructor
    Synth(double amp = 1.0, int voices = 1);
    ~Synth();
    // methods
    void tick();
    // setters
    void setSampleRate(float sampleRate);
    void setAmp(double amp);
    // getters
    float getSample();
    float getPhase();
};

#endif /* Synth_hpp */
