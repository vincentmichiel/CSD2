//
//  Reverb.cpp
//  Autoverb
//
//  Created by Vincent Van den Broeck on 23/03/2024.
//

#include "Reverb.hpp"
#include "MultitapDelay.hpp"
#include <iostream>

DelayLine::~DelayLine(){
    delete delay1;
    delete delay2;
    delete multitapdelay;
    delete allpassfilter;
}

void DelayLine::tick(){
    delay1->tick();
    delay2->tick();
    multitapdelay->tick();
}

tripleOutput DelayLine::process(float input, float previousDelayInput){
    // init values
    tripleOutput output;
    
    // sum input
    input = input + previousDelayInput;
    input *= 0.5;
    // allpass filter
    input = allpassfilter->process(input);
    // delays
    input = delay1->process(input) + input * 0.5;
    input = delay2->process(input) + input * 0.5;
    
    // store output for next delayLine
    output.multiOut[0] = input * feedback;
    
    doubleOutput doubleoutput;
    // multiTap to LR sum
    doubleoutput = multitapdelay->applyEffectDouble(input);
    output.multiOut[1] = doubleoutput.multiOut[0];
    output.multiOut[2] = doubleoutput.multiOut[1];
    
    return output;
}

Reverb::~Reverb(){
    for(int i = 0; i < 8; i++){
        delete delaylines[i];
    }
    Effect::~Effect();
}

void Reverb::tick(){
    for(int i = 0; i < 8; i++){
        delaylines[i]->tick();
    }
}

float Reverb::process(float input, int channel){
    if(channel == 0){
        output.multiOut[0] = input;
        LSum = 0;
        RSum = 0;
        
        for(int i = 0; i < 8; i++){
            output = delaylines[i]->process(input, output.multiOut[0]);
            LSum += output.multiOut[1];
            RSum += output.multiOut[2];
        }
        output.multiOut[1] /= 8.0;
        output.multiOut[2] /= 8.0;
        
        return output.multiOut[1];
    } else {
        return output.multiOut[2];
    }
}
