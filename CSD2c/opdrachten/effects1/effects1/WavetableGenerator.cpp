//
//  WavetableGenerator.cpp
//  effects1
//
//  Created by Vincent Van den Broeck on 18/02/2024.
//

#include "WavetableGenerator.hpp"

void WavetableGenerator::generateWaveform(float* buffer, int numFrames,
                                          WaveformType waveformType) {
    Oscillator* osc;
    float freq = 1.0;
    switch(waveformType) {
        case WaveformType::SINE:
        {
            osc = new Sine(freq, 1, numFrames);
            break;
        }
        case WaveformType::SAW:
        {
            osc = new Saw(freq, 1, numFrames);
            break;
        }
        case WaveformType::SQUARE:
        {
            // TODO: alter calculation of to create a non-aliasing square,
            // similar to the calculation within the Saw class
            osc = new Square(freq, 1, numFrames);
            break;
        }
        default:
            throw "WavetableGenerator::WavetableGenerator - incorrect waveformType.";
            break;
    }
    
    for(int i = 0; i < numFrames; i++) {
        buffer[i] = osc->getSample();
        osc->tick();
    }
    // release dynamically allocated oscillator object
    delete osc;
    osc = nullptr;
}
