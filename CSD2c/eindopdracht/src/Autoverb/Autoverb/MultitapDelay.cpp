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

float MultitapDelay::applyEffect(int channel, float sample){
    float taps = 0;
    float output = 0;
  
    // read taps
    for(int i = channel; i < tapAmount; i += 2){
        taps++;
        output += circBuffer.readTap(i);
    }
    output /= taps;
   
    // delay
    circBuffer.write(sample);
    return output;
}
