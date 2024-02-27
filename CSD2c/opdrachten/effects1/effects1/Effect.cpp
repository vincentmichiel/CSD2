//
//  Effect.cpp
//  effects1
//
//  Created by Vincent Van den Broeck on 08/02/2024.
//

#include "Effect.hpp"
#include <iostream>

Effect::Effect(float mix) : mix(mix){
    bypass = false;
}

Effect::~Effect(){};

void Effect::setBypass(bool bypass){
    this->bypass = bypass;
}

void Effect::setMix(float mix){
    this->mix = mix;
}

float Effect::applyEffect(float sample){
    return sample;
}

float Effect::applyEffect(int channel, float sample){
    return sample;
}

float Effect::process(float sample){
    // bypass
    if(bypass){
        return sample;
    }

    // process
    float output = applyEffect(sample);
    
    // drywet
    output *= mix;
    output += sample * 1 - mix;
    
    // output
    return output;
}

float Effect::process(int channel, float sample){
    // bypass
    if(bypass){
        return sample;
    }

    // process
    float output = applyEffect(channel, sample);
    
    // drywet
    output *= mix;
    output += sample * 1 - mix;
    
    // output
    return output;
}
