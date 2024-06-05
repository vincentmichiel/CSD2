//
//  Oscillator.cpp
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 04/12/2023.
//

#include "Oscillator.hpp"
#include <iostream>

Oscillator::Oscillator(float frequency, float amplitude, float samplerate) : frequency(frequency),
amplitude(amplitude), phase(0), sample(0), samplerate(samplerate)
{
    sampleDuration = frequency / samplerate;
}

Oscillator::~Oscillator() {
    
}

void Oscillator::setSamplerate(float samplerate){
    this->samplerate = samplerate;
    sampleDuration = frequency / samplerate;
}

void Oscillator::setFrequency(float frequency){
    this->frequency = frequency;
    sampleDuration = frequency / samplerate;
}

void Oscillator::setAmplitude(float amplitude){
    this->amplitude = amplitude;
}

void Oscillator::setPhase(float phase){
    phaseOffset = phase;
    this->phase = phase;
    if(this->phase > 1.0f) this->phase -= 1.0f;
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

float Oscillator::getPhaseOffset(){
    return phaseOffset;
}

void Oscillator::tick(){
    // update phase
    phase += sampleDuration;
    if(phase > 1.0f) phase -= 1.0f;
}

std::string Oscillator::getOscillatorType(){
    return "default";
}

void Sine::tick(){
    Oscillator::tick();
    // calculate sample
    sample = sin(pi * 2 * phase) * amplitude;
}

std::string Sine::getOscillatorType(){
    return "sine";
}

void Block::tick(){
    Oscillator::tick();
    // calculate sample
    sample = (sin(pi * 2 * phase) > 0 ? 1 : -1) * amplitude;
}

std::string Block::getOscillatorType(){
    return "square";
}

void Saw::tick() {
    Oscillator::tick();
    
    //add 0.5 to phase, to allow a regular sawwave
    
    wPhase = phase + 0.5;
    //we want values between: [0.0, 1.0], so wrap it
    if(wPhase > 1) wPhase -= 1.0;
    
    //calculate the pure sawwave
    sample = wPhase * 2.0 - 1.0;
    
    //we want to apply smoothing to prevent aliasing
    //using Polynomial to smooth the corners of the sawwave
    if(wPhase < phaseIncrement) {
        smoothY = wPhase / phaseIncrement;
        smoothY = smoothY + smoothY - smoothY * smoothY - 1.0;
    } else if (wPhase > 1.0 - phaseIncrement) {
        smoothY = (wPhase - 1.0) / phaseIncrement;
        smoothY = smoothY + smoothY + smoothY * smoothY + 1.0;
    } else {
        smoothY = 0;
    }
    sample -= smoothY;
}

std::string Saw::getOscillatorType(){
    return "saw";
}
