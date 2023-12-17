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
    float phase;
    double midiNoteToFrequency(int midiNote);
    
protected:
    double amp;
    int voices;
    // array of oscillators
    std::vector<std::unique_ptr<Oscillator>> oscillators;
    
public:
    // constructor destructor
    Synth(double amp = 1.0, int voices = 1);
    virtual ~Synth();
    // methods
    void tick();	
    // setters
    void setSampleRate(float sampleRate);
    void setAmp(double amp);
    // getters
    virtual float getSample();
    float getPhase();
    virtual void setOscillatorAmp(int voice, double amp) = 0;
};

#endif /* Synth_hpp */
