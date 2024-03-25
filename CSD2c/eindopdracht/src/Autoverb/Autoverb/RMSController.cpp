//
//  RMSController.cpp
//  Autoverb
//
//  Created by Vincent Van den Broeck on 24/03/2024.
//

#include "RMSController.hpp"
#include <cmath>

RMSController::RMSController(uint bufferSize) : bufferSize(bufferSize){
    buffer = new CircBuffer(bufferSize, 1);
    controlValueHistory = new CircBuffer(bufferSize, 1);
}

RMSController::~RMSController(){
    delete buffer;
    delete controlValueHistory;
}

float RMSController::getControlValue(){
    calcRMS();
    float averageValue = 0;
    for(int i = 0; i < bufferSize; i++){
        averageValue += controlValueHistory->readAtIndex(i);
    }
    averageValue /= (float)bufferSize;
    
    return averageValue;
}

void RMSController::calcRMS(){
    float total = 0;
    float val;
    
    // read from buffer
    for(int i = 0; i < bufferSize; i++){
        val = abs(buffer->readAtIndex(i));
        total = total + (val * val);
    }
    
    // calc rms
    rms = (1.0 / bufferSize) * total;
    controlValue = 100 * rms;
    
    controlValueHistory->write(controlValue);
}

void RMSController::write(float sample){
    buffer->write(sample);
}

void RMSController::tick(){
    buffer->tick();
    controlValueHistory->tick();
}


