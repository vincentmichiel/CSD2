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
    output.multiOut[0] = input * feedback / 8.0f;
    
    doubleOutput doubleoutput;
    // multiTap to LR sum
    doubleoutput = multitapdelay->applyEffectDouble(input);
    output.multiOut[1] = doubleoutput.multiOut[0];
    output.multiOut[2] = doubleoutput.multiOut[1];
    
    return output;
}

Reverb::~Reverb(){
    for(int i = 0; i < 16; i++){
        delete delaylines[i];
    }
    delete earlyReflections;
    delete preDelay;
    delete modDelay1;
    delete modDelay2;
    
    delete inputHPF;
    for(int i = 0; i < 2; i++){
        delete outputLPF[i];
        delete LPF[i];
    }
    Effect::~Effect();
}

void Reverb::tick(){
    for(int i = 0; i < 16; i++){
        delaylines[i]->tick();
    }
    earlyReflections->tick();
    preDelay->tick();
    modDelay1->tick();
    modDelay2->tick();
}

float Reverb::process(float input, int channel){
    if(channel == 0){
        input = inputHPF->process(input);
        // pre
        preOutput = earlyReflections->applyEffectDouble(input);
        
        input = preDelay->process(input);
        
        LSum = 0;
        RSum = 0;
        
        for(int i = 0; i < 16; i++){
            output = delaylines[i]->process(input, output.multiOut[0]);
            LSum += output.multiOut[1];
            RSum += output.multiOut[2];
            
            if(i == 7){
                output.multiOut[0] = LPF[0]->process(modDelay1->process(output.multiOut[0]));
            } else if(i == 15){
                output.multiOut[0] = LPF[1]->process(modDelay2->process(output.multiOut[0]));
            }
        }
        
        LSum += preOutput.multiOut[0];
        RSum += preOutput.multiOut[1];
        LSum /= 18.0;
        RSum /= 18.0;
        
        return outputLPF[0]->process(output.multiOut[1]);
    } else {
        return outputLPF[1]->process(output.multiOut[2]);
    }
}
