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

struct tripleOutput {
    float multiOut[3];
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
        delay1 = new Delay(samplerate, delayTimes[0], delayTimes[0], -0.5);
        delay2 = new Delay(samplerate, delayTimes[1], delayTimes[1], -0.5);
        
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
    uint delayTimes[8][4] = {
        {1, 3, 4, 5},
        {2, 4, 2, 3},
        {3, 2, 4, 5},
        {2, 3, 4, 5},
        {5, 7, 4, 8},
        {2, 5, 8, 5},
        {1, 4, 7, 3},
        {3, 6, 9, 8}
    };
    
    float allpassDelays[8] = { 1, 3, 2, 4, 7, 6, 4, 9};
    DelayLine * delaylines[8];
    tripleOutput output;
    float LSum = 0;
    float RSum = 0;
    
public:
    Reverb(float samplerate, float feedback) {
        for(int i = 0; i < 8; i++){
            delaylines[i] = new DelayLine(samplerate, feedback, delayTimes[i], allpassDelays[i]);
        }
    }
    
    ~Reverb();
    
    float process(float input, int channel);
    void tick();
};

#endif /* Reverb_hpp */
