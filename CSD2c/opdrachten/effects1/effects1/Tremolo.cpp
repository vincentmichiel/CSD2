//
//  Tremolo.cpp
//  effects1
//
//  Created by Vincent Van den Broeck on 08/02/2024.
//

#include "Tremolo.hpp"
#include "Oscillator.hpp"
#include <iostream>

Tremolo::~Tremolo(){
    Effect::~Effect();
};

void Tremolo::setSampleRate(float sampleRate){
    LFO.setSamplerate(sampleRate);
}

void Tremolo::setDepth(float depth){
    this->depth = depth;
}

void Tremolo::setFrequency(float frequency){
    this->frequency = frequency;
    LFO.setFrequency(frequency);
}

float Tremolo::getDepth(){
    return depth;
}

float Tremolo::getFrequency(){
    return frequency;
}

float Tremolo::applyEffect(float sample){
    // transform sine in range [-1, 1] to range [0, 1]
    float modSignal = LFO.getSample() * 0.5 + 0.5;
    // apply modDept
    modSignal *= depth;
    modSignal += 1.0 - depth;
    // apply modulation signal to input
    return sample * modSignal;
}

void Tremolo::tick(){
    LFO.tick();
}
