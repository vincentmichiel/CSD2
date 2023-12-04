//
//  Oscillator.cpp
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 04/12/2023.
//

#include "Oscillator.hpp"

Oscillator::Oscillator(float frequency, float amplitude, float samplerate) : frequency(frequency),
  amplitude(amplitude), phase(0), sample(0), samplerate(samplerate)
{
    sampleDuration = frequency / samplerate;
    nextCycle = false;
}

Oscillator::~Oscillator() {
  
}

void Oscillator::setSamplerate(float samplerate){
    this->samplerate = samplerate;
    sampleDuration = frequency / samplerate;
}

void Oscillator::setFrequency(float frequency){
    this->frequency = frequency;
    sampleDuration = sample / samplerate;
}

void Oscillator::setAmplitude(float amplitude){
    this->amplitude = amplitude;
}

double Oscillator::getFrequency(){
    return frequency;
}

double Oscillator::getAmplitude(){
    return amplitude;
}

float Oscillator::getSample(){
    return sample;;
}

float Oscillator::getPhase(){
    return phase;
}

void Oscillator::tick(){
    // update phase
    phase += sampleDuration;
    if(phase > 1.0f) {
        phase -= 1.0f;
        nextCycle = true;
    }
}

void Sine::tick(){
    Oscillator::tick();
    // calculate sample
    sample = sin(pi * 2 * phase) * amplitude;
}

void Square::tick(){
    Oscillator::tick();
    // calculate sample
    sample = (sin(pi * 2 * phase) > 0 ? 1 : -1) * amplitude;
}

void Triangle::tick() {
    Oscillator::tick();
    
    // Create a triangle wave using an absolute sawtooth
    sample = (-2.0f * abs(phase - 0.5f)) * amplitude;
}
