/*
  ==============================================================================

    Interpolate.h
    Created: 12 May 2024 3:26:46pm
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#pragma once

#include <stdio.h>

class Interpolate {
public:
    static float nnMap(float value, float low, float high);
    static float linMap(float value, float low, float high);
    static float mapInRange(float value, float minIn, float maxIn, float minOut, float maxOut);
};
