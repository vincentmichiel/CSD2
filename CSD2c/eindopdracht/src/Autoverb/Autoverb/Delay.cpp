//
//  Delay.cpp
//  effects1
//
//  Created by Vincent Van den Broeck on 08/02/2024.
//

#include "Delay.hpp"
#include <iostream>

Delay::~Delay(){
    Effect::~Effect();
};

void Delay::setFeedback(float feedback){
    this->feedback = feedback;
}

uint Delay::getSize(){
    return size;
}

uint Delay::getDistance(){
    return distance;
}

float Delay::getFeedback(){
    return feedback;
}

void Delay::tick(){
    circBuffer.tick();
}

float Delay::applyEffect(float sample){
    // read sample from delayline
    float delayedSample = circBuffer.read();
    
    // delay + feedback
    circBuffer.write(sample + delayedSample * feedback);
    
    // output
    return delayedSample;
}
