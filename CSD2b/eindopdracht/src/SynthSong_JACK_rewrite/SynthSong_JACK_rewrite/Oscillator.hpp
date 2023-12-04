//
//  Oscillator.hpp
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 04/12/2023.
//

#ifndef Oscillator_hpp
#define Oscillator_hpp

#include <stdio.h>
#include <math.h>

class Oscillator {
public:
    Oscillator(float frequency = 440, float amplitude = 1, float samplerate = 44100);
    ~Oscillator();
    void setSamplerate(float samplerate);
    void setFrequency(float frequency);
    void setAmplitude(float amplitude);
    double getFrequency();
    double getAmplitude();
    float getSample();
    float getPhase();

protected:
    const float pi = acos (-1);  //atan(1) * 4; <-- vak van Pieter.
    float frequency;
    float amplitude;
    float phase;
    // sample contains the current sample
    float sample;
    float sampleDuration;
    virtual void tick() = 0;
    
private:
    float samplerate;
};

class Sine : public Oscillator {
public:
    void tick();
    using Oscillator::Oscillator;
};

class Square : public Oscillator {
public:
    void tick();
    using Oscillator::Oscillator;
};


#endif /* Oscillator_hpp */
