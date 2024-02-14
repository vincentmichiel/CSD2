//
//  Interpolate.cpp
//  effects1
//
//  Created by Vincent Van den Broeck on 13/02/2024.
//

#include "Interpolate.hpp"

float Interpolate::nnMap(float value, float low, float high){
    if(value >= 0 && value <= 1){
        return value < 0.5f ? low : high;
    } else {
        return 0;
    }
}

float Interpolate::linMap(float value, float low, float high){
    if(value >= 0 && value <= 1){
        float output = (1.0f - value) * low;
        output += value * high;
        return output;
    } else {
        return 0;
    }
}

float Interpolate::mapInRange(float value, float minIn, float maxIn, float minOut, float maxOut){
    // Calculate the scaling factor
    float scale = (maxOut - minOut) / (maxIn - minIn);

    // Map the input value to the output range
    float output = (value - minIn) * scale + minOut;

    return output;
}
