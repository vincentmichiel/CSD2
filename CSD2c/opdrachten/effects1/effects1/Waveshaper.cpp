//
//  Waveshaper.cpp
//  effects1
//
//  Created by Vincent Van den Broeck on 13/02/2024.
//

#include "Waveshaper.hpp"
#include "Interpolate.hpp"
#include "WavetableGenerator.hpp"
#include <iostream>
#include <fstream>

Waveshaper::~Waveshaper(){
    Effect::~Effect();
};

Waveshaper::Waveshaper(float drive) : Effect(), drive(drive) {
    WavetableGenerator::generateWaveform(wavetable, BUFFER_SIZE, drive);
}

void Waveshaper::setDrive(float drive){
    this->drive = drive;
    WavetableGenerator::generateWaveform(wavetable, BUFFER_SIZE, drive);
}

float Waveshaper::applyEffect(int channel, float sample){
    sample = Interpolate::mapInRange(sample, -1, 1, 0, BUFFER_SIZE - 1);
    // transform floating point index to integer index
    int i = (int) sample;
    // retrieve restvalue floating point index (value after comma)
    float restValue = sample - i;
    float low = wavetable[i];
    float high = wavetable[i + 1];
    
    // wrap high
    if(high >= BUFFER_SIZE) high = BUFFER_SIZE - 1;
    
    float delta = high - low;
    float value = (restValue * delta) + low;
    
    return value;
}

void Waveshaper::plot(){
    // clear plot file
    std::ofstream ofs;
    ofs.open("waveform.txt", std::ofstream::out | std::ofstream::trunc);
    
    for(int i = 0; i < BUFFER_SIZE; i++){
        ofs << i << ":" << wavetable[i] << std::endl;
    }
    
    // close file
    ofs.close();
}
