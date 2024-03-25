//
//  Reverb.hpp
//  Autoverb
//
//  Created by Vincent Van den Broeck on 23/03/2024.
//

#ifndef Reverb_hpp
#define Reverb_hpp

#include <stdio.h>
#include "Effect.hpp"
#include "Delay.hpp"
#include "Moddelay.hpp"
#include "MultitapDelay.hpp"
#include "AllpassFilter.hpp"
#include "Filters.h"

struct tripleOutput {
    float multiOut[3];
};

struct ch16 {
    float multiOut[16];
};

class DelayLine {
private:
    float feedback;
    Delay * delay1;
    Delay * delay2;
    MultitapDelay * multitapdelay;
    AllPassFilter * allpassfilter;
    
public:
    DelayLine(){};
    DelayLine(float samplerate, float feedback, uint * delayTimes, float allpassDelay) : feedback(feedback) {
        // init delay
        delay1 = new Delay(samplerate, delayTimes[0], delayTimes[0], -0.8);
        delay2 = new Delay(samplerate, delayTimes[1], delayTimes[1], -0.8);
        
        // init multitap delay
        uint distances[2] = {delayTimes[2], delayTimes[3]};
        
        if(delayTimes[2] >= delayTimes[3]){
            multitapdelay = new MultitapDelay(samplerate, delayTimes[2], distances, 2);
        } else {
            multitapdelay = new MultitapDelay(samplerate, delayTimes[3], distances, 2);
        }
        // init allpass
        allpassfilter = new AllPassFilter(allpassDelay, 0.5);
    }
    
    ~DelayLine();
    tripleOutput process(float input, float previousDelayInput);
    void tick();
};

class Reverb : public Effect {
private:
    uint earlyReflectionTimes[12] = {8, 10, 14, 17, 22, 27, 29, 33, 40, 42, 47, 50};
    uint delayTimes[16][4] = {
        {55, 44, 20, 15},
        {48, 30, 27, 23},
        {65, 57, 28, 24},
        {33, 45, 21, 15},
        {79, 66, 74, 54},
        {93, 73, 27, 40},
        {31, 38, 54, 42},
        {32, 24, 43, 38},
        {33, 44, 20, 19},
        {24, 33, 27, 28},
        {50, 48, 30, 21},
        {61, 58, 19, 16},
        {32, 27, 35, 42},
        {45, 50, 62, 67},
        {31, 38, 41, 43},
        {69, 61, 43, 41}
    };
    
    float allpassDelays[16] = {30, 50, 45, 23, 80, 93, 46, 35, 40, 34, 88, 45, 21, 43, 28, 31};
    MultitapDelay * earlyReflections;
    MultitapDelay * diffuser;
    Delay * preDelay;
    DelayLine * delaylines[16];
    Moddelay * modDelay1;
    Moddelay * modDelay2;
    Biquad * inputHPF;
    OnePole * outputLPF[2];
    OnePole * LPF[2];
    tripleOutput output;
    doubleOutput preOutput;
    ch16 inputSplit;
    float LSum = 0;
    float RSum = 0;
    
public:
    Reverb(float samplerate, float feedback) {
        earlyReflections = new MultitapDelay(samplerate, 51, earlyReflectionTimes, 12);
        
        // diffusers
        for(int i = 0; i < 2; i++){
            uint multiInputDelays[16];
            for(int i = 0; i < 16; i++){
                multiInputDelays[i] = rand() % 79 + 1;
            }
            diffuser = new MultitapDelay(samplerate, 80, multiInputDelays, 16);
        }
        
        preDelay = new Delay(samplerate, 81, 80, 0.0);
        
        // moddelays
        modDelay1 = new Moddelay(samplerate, 200, 172, 199, 0.2);
        modDelay2 = new Moddelay(samplerate, 250, 230, 249, 0.2);
        modDelay2->setPhase(0.5);
        
        // delaylines
        for(int i = 0; i < 16; i++){
            delaylines[i] = new DelayLine(samplerate, feedback, delayTimes[i], allpassDelays[i]);
        }
        output.multiOut[0] = 0;
        
        // filters
        inputHPF = new Biquad();
        inputHPF->setCoefficients(0.9899759179893742,
                                  -1.9799518359787485,
                                  0.9899759179893742,
                                  -1.979851353142371,
                                  0.9800523188151258);
        
        for(int i = 0; i < 2; i++){
            outputLPF[i] = new OnePole();
            outputLPF[i]->setCoefficient(0.4);
            LPF[i] = new OnePole();
            LPF[i]->setCoefficient(0.8);
        }
    }
    
    ~Reverb();
    
    float applyEffect(int channel, float sample) override;
    void tick();
};

#endif /* Reverb_hpp */
