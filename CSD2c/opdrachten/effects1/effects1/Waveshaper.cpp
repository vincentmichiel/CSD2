//
//  Waveshaper.cpp
//  effects1
//
//  Created by Vincent Van den Broeck on 13/02/2024.
//

#include "Waveshaper.hpp"
#include "Interpolate.hpp"
#include <math.h>

void Waveshaper::setDrive(float drive){
    this->drive = drive;
}

float Waveshaper::applyEffect(float sample){
    
    //       1
    // (--------- ) * arctan(kx)
    //   arctan(k)
    
    float output = (1.0f / atan(drive)) * atan(drive * sample);
    
    return output;
}
