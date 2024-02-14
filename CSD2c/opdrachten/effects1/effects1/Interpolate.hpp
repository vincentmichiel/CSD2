//
//  Interpolate.hpp
//  effects1
//
//  Created by Vincent Van den Broeck on 13/02/2024.
//

#ifndef Interpolate_hpp
#define Interpolate_hpp

#include <stdio.h>

class Interpolate {
public:
    static float nnMap(float value, float low, float high);
    static float linMap(float value, float low, float high);
    static float mapInRange(float value, float minIn, float maxIn, float minOut, float maxOut);
};

#endif /* Interpolate_hpp */
