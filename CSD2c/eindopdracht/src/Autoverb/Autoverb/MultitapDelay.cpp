//
//  MultitapDelay.cpp
//  Autoverb
//
//  Created by Vincent Van den Broeck on 22/03/2024.
//

#include "MultitapDelay.hpp"
#include <iostream>

MultitapDelay::~MultitapDelay(){
    Effect::~Effect();
};

uint MultitapDelay::getSize(){
    return size;
}

uint* MultitapDelay::getDistances(){
    return distances;
}

void MultitapDelay::tick(){
    circBuffer.tick();
}

doubleOutput MultitapDelay::applyEffectDouble(float sample){
    doubleOutput output;
    float taps = 0;
    float sum = 0;
  
    for(int channel = 0; channel < 2; channel++){
        // read taps
        for(int i = channel; i < tapAmount; i += 2){
            taps++;
            sum += circBuffer.readTap(i);
        }
        sum /= taps;
        output.multiOut[channel] = sum;
    }
   
    // delay
    circBuffer.write(sample);
    return output;
}
