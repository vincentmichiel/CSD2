//
//  WavetableGenerator.hpp
//  effects1
//
//  Created by Vincent Van den Broeck on 18/02/2024.
//

#ifndef WavetableGenerator_hpp
#define WavetableGenerator_hpp

#include <stdio.h>
#include <iostream>
#include "Oscillator.hpp"

class WavetableGenerator
{
public:
  enum WaveformType {
    SINE = 0, // ensure enum starts at 0
    SAW,
    SQUARE,
    SIZE // 4
  };
  static void generateWaveform(float* buffer, int numFrames,
    WaveformType waveformType);
    static void generateWaveform(float* buffer, int numFrames, float drive);

private:
  // hide default constructor
  WavetableGenerator() {};
};

#endif /* WavetableGenerator_hpp */
