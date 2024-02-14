//
//  Effect.cpp
//  effects1
//
//  Created by Vincent Van den Broeck on 08/02/2024.
//

#include "Effect.hpp"
#include <iostream>

Effect::Effect(float mix) : mix(mix){
    
}

void Effect::setMix(float mix){
    this->mix = mix;
}

float Effect::process(float sample){
    // process
    float output = applyEffect(sample);
    
    // drywet
    output *= mix;
    output += sample * 1 - mix;
    
    // output
    return output;
}
