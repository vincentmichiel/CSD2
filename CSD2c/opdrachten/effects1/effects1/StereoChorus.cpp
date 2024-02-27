//
//  StereoChorus.cpp
//  effects1
//
//  Created by Vincent Van den Broeck on 23/02/2024.
//

#include "StereoChorus.hpp"
#include <iostream>

StereoChorus::~StereoChorus(){
    delete lfo[0];
    delete lfo[1];
    Effect::~Effect();
}

void StereoChorus::tick(){
    for(int channel = 0; channel < 2; channel++){
        buffer[channel]->tick();
        lfo[channel]->tick();
        
        buffer[channel]->setDistanceRW(delaySamples + (offsetSamples * lfo[channel]->getSample()));
    }
}

float StereoChorus::applyEffect(int channel, float sample){
    buffer[channel]->write(sample);
    return buffer[channel]->read();
}

uint StereoChorus::getSize(){
    return size;
}

uint StereoChorus::getDistance(){
    return distance;
}
