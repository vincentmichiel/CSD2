//
//  Oscillator.hpp
//  SynthSong
//
//  Created by Vincent Van den Broeck on 07/11/2023.
//

#ifndef Oscillator_hpp
#define Oscillator_hpp

#include <stdio.h>
#include <thread>
#include <random>
#include "Constants.hpp"
#include "audio_io.hpp"

enum class OscillatorType {
    Sine,
    Square,
    Triangle,
    Noise
};

class Oscillator {
private:
    float samplebuffer[FRAMESPERBUFFER * NROFCHANNELS];
    unsigned long bufptr=0; // pointer into sample buffer
    unsigned long x; // sample index
    bool playState;
    int output_device;
    Audio_IO audiostream;
    std::thread audioThread;
    void audioCallback();
    virtual float sampleGenerator(unsigned long timeIndex);
    
protected:
    double freq;
    double amp;
    
public:
    Oscillator(double initFreq = 440.0, double initAmp = 0.5, int initOutputDevice = 0);
    ~Oscillator();
    void setFreq(double newFreq);
    void setAmp(double newAmp);
    double getAmp();
    void start();
    void stop();
};

class Sine : public Oscillator {
private:
    float sampleGenerator(unsigned long timeIndex) override;
public:
    using Oscillator::Oscillator;
};

class Square : public Oscillator {
private:
    double dutyCycle;
    float sampleGenerator(unsigned long timeIndex) override;
public:
    Square(double initFreq = 440.0, double initAmp = 0.5, double initDutyCycle = 0.5, int initOutputDevice = 0);
};

class Triangle : public Oscillator {
private:
    float sampleGenerator(unsigned long timeIndex) override;
    using Oscillator::Oscillator;
};

class Noise : public Oscillator {
private:
    // make setfreq inaccessible for noise class
    using Oscillator::setFreq;
    // random engine
    std::default_random_engine randomEngine;
    std::uniform_real_distribution<float> distribution;
    float sampleGenerator(unsigned long timeIndex) override;
public:
    Noise(double initAmp = 0.5);
};

#endif /* Oscillator_hpp */
