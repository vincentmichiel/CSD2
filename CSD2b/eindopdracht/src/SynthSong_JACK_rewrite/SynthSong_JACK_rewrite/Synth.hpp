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
    float frequency;
    int voices;
    // array of oscillators
    std::vector<std::unique_ptr<Oscillator>> oscillators;
    
public:
    // constructor destructor
    Synth(float frequency = 440, double amp = 1.0, int voices = 1);
    virtual ~Synth();
    // methods
    virtual void tick();	
    // setters
    void setSampleRate(float sampleRate);
    void setAmp(double amp);
    virtual void setFrequency(float frequency);
    void setNote(int note);
    virtual void setOscillatorAmp(int voice, double amp) = 0;
    virtual void setRatio(int ratio);
    virtual void setDepth(float depth);
    // getters
    virtual float getSample();
    float getPhase();
    float getFrequency();
    double getAmp();
    std::string getOscillatorType(int oscillator);
};

#endif /* Synth_hpp */
