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
#include "Constants.hpp"
#include "audio_io.hpp"

class Oscillator {
protected:
    float samplebuffer[FRAMESPERBUFFER * NROFCHANNELS];
    unsigned long bufptr=0; // pointer into sample buffer
    double freq;
    double phase;
    double amp;
    unsigned long x; // sample index
    bool playState;
    int output_device;
    Audio_IO audiostream;
    void audioCallback();
    std::thread audioThread;
    
    
public:
    Oscillator(double initFreq = 440.0, double initAmp = 0.5, double initPhase = 0.0, int initOutputDevice = 0);
    ~Oscillator();
    void setFreq(double newFreq);
    void setAmp(double newAmp);
    void setPhase(double newPhase);
    void start();
    void stop();
};

class Sine : public Oscillator {
public:
    using Oscillator::Oscillator;
};

class Square : public Oscillator {
public:
    Square(double initFreq, double initAmp, double initPhase, double initDutyCycle, int initOutputDevice);
    
private:
    double dutyCycle;
};

class Triangle : public Oscillator {
    using Oscillator::Oscillator;
};

class Noise : public Oscillator {
public:
    Noise(double initAmp);
};

#endif /* Oscillator_hpp */
