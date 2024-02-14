//
//  Waveshaper.cpp
//  effects1
//
//  Created by Vincent Van den Broeck on 13/02/2024.
//

#include "Waveshaper.hpp"
#include "Interpolate.hpp"
#include <math.h>

void Waveshaper::setRatio(float ratio){
    this->ratio = ratio;
}

float Waveshaper::applyEffect(float sample){
    
    //       1
    // (--------- ) * arctan(kx)
    //   arctan(k)
    
    float output = (1.0f / atan(ratio)) * atan(ratio * sample);
    
    return output;
}
