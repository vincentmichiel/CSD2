//
//  FMSynth.cpp
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 17/12/2023.
//

#include "FMSynth.hpp"

FMSynth::FMSynth(double amp, int voices) : Synth(amp, voices){
    
}

FMSynth::~FMSynth(){
    
}

float FMSynth::getSample(){
   
    
    return 0.0;
}

void FMSynth::setOscillatorAmp(int voice, double newAmp){
    if(voice >= 0 && voice < voices){
        oscillators[voice]->setAmplitude(newAmp);
    } else {
        std::cout << "could not set new amplitude for oscillator: index out of bounds" << std::endl;
    }
}

