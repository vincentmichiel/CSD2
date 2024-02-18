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
#include <iostream>

#define SAW_SMOOTH_FACTOR 5.0f

class Oscillator {
public:
    // constructor destructor
    Oscillator(float frequency = 440, float amplitude = 1, float samplerate = 44100);
    virtual ~Oscillator();
    //methods
    virtual void tick() = 0;
    // setters
    void setSamplerate(float samplerate);
    void setFrequency(float frequency);
    void setAmplitude(float amplitude);
    void setPhase(float phase);
    // getters
    double getFrequency();
    double getAmplitude();
    float getSample();
    float getPhase();
    virtual std::string getOscillatorType();
    
protected:
    const float pi = acos (-1);  //atan(1) * 4; <-- vak van Pieter.
    float frequency;
    float amplitude;
    float phase;
    // sample contains the current sample
    float sample;
    
private:
    float samplerate;
    float sampleDuration;
};

class Sine : public Oscillator {
public:
    void tick() override;
    using Oscillator::Oscillator;
    std::string getOscillatorType() override;
};

class Square : public Oscillator {
public:
    void tick() override;
    using Oscillator::Oscillator;
    std::string getOscillatorType() override;
};

class Saw : public Oscillator {
public:
    void tick() override;
    Saw(float frequency = 440, float amplitude = 1, float samplerate = 44100) : Oscillator(frequency, amplitude, samplerate), phaseIncrement(frequency / samplerate * SAW_SMOOTH_FACTOR),
    smoothY(0){};
    std::string getOscillatorType() override;
private:
    // ---- values used to calculate the saw wave ----
    //phase increment
    const float phaseIncrement;
    // value used for smoothing the transition from -1 to 1
    float smoothY;
    //wrapped phase
    float wPhase;
};


#endif /* Oscillator_hpp */
