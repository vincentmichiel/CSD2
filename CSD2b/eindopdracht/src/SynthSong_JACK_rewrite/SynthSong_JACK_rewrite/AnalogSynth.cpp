//
//  AnalogSynth.cpp
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 17/12/2023.
//

#include "AnalogSynth.hpp"
#include<cmath>
#include<iostream>

AnalogSynth::AnalogSynth(double amp, int voices) : Synth(amp, voices) {
    this->amp = amp;
    this->voices = voices;
    
    // clear existing oscillators
    oscillators.clear();
    
    oscillators.push_back(std::make_unique<Sine>());
    oscillators.push_back(std::make_unique<Triangle>());
    oscillators.push_back(std::make_unique<Square>());
    
    // adjust phase relations
    for(int i = 0; i < voices; i++){
        oscillators[i]->setPhase((i / static_cast<float>(voices)) * 2 * M_PI);
    }
}

AnalogSynth::~AnalogSynth(){
    
}

float AnalogSynth::getSample(){
    float sample = 0;
    for(int i = 0; i < voices; i++){
        sample += oscillators[i]->getSample();
    }
    sample /= voices;
    return sample;
}

void AnalogSynth::setOscillatorAmp(int voice, double newAmp){
    oscillators[0]->setFrequency(220);
    oscillators[1]->setFrequency(400);
    if(voice >= 0 && voice < voices){
        oscillators[voice]->setAmplitude(newAmp);
    } else {
        std::cout << "could not set new amplitude for oscillator: index out of bounds" << std::endl;
    }
}
