//
//  MultitapDelay.cpp
//  Autoverb
//
//  Created by Vincent Van den Broeck on 22/03/2024.
//

#include "MultitapDelay.hpp"

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

float MultitapDelay::applyEffect(float sample){
    // read sample from delayline
    float delayedSample = circBuffer.readTaps();
    
    // delay + feedback
    circBuffer.write(sample);
    
    // output
    return delayedSample;
}
