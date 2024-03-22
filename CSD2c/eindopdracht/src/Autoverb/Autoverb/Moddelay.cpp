//
//  Moddelay.cpp
//  Autoverb
//
//  Created by Vincent Van den Broeck on 22/03/2024.
//

#include "Moddelay.hpp"

Moddelay::~Moddelay(){
    Effect::~Effect();
};

void Moddelay::setFeedback(float feedback){
    this->feedback = feedback;
}

uint Moddelay::getSize(){
    return size;
}

float Moddelay::getFeedback(){
    return feedback;
}

void Moddelay::tick(){
    // modulate delay time
    float modSignal = (LFO.getSample() + 1) * 0.5;
    circBuffer.setDistanceRW(start + ((end - start) * modSignal));
    
    circBuffer.tick();
    LFO.tick();
}

float Moddelay::applyEffect(float sample){
    // read sample from delayline
    float delayedSample = circBuffer.read();
    
    // delay + feedback
    circBuffer.write(sample + delayedSample * feedback);
    
    // output
    return delayedSample;
}
