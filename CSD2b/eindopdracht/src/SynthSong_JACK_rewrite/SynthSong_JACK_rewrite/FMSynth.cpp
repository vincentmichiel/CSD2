//
//  FMSynth.cpp
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 17/12/2023.
//

#include "FMSynth.hpp"

FMSynth::FMSynth(float frequency, double amp, int voices) : Synth(frequency, amp, voices){
    ratio = 1;
    depth = 0.0;
    setFrequency(frequency);
}

FMSynth::~FMSynth(){
    
}

void FMSynth::setFrequency(float frequency){
    Synth::setFrequency(frequency);
    oscillators[1]->setFrequency(oscillators[1]->getFrequency() * ratio);
}

void FMSynth::tick(){
    // FM MAGIC
    oscillators[0]->setFrequency(frequency + oscillators[1]->getSample() * (depth * 15000));
    
    Synth::tick();
}

void FMSynth::setRatio(int ratio){
    this->ratio = ratio;
    oscillators[1]->setFrequency(frequency * ratio);
}

void FMSynth::setDepth(float depth){
    this->depth = depth;
}

void FMSynth::setOscillatorAmp(int voice, double newAmp){
    if(voice >= 0 && voice < voices){
        oscillators[voice]->setAmplitude(newAmp);
    } else {
        std::cout << "could not set new amplitude for oscillator: index out of bounds" << std::endl;
    }
}

float FMSynth::getSample(){
    return oscillators[0]->getSample() * amp;
}

int FMSynth::getRatio(){
    return ratio;
}

float FMSynth::getDepth(){
    return depth;
}

