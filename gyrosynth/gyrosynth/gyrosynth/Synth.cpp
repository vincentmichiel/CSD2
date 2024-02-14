//
//  Synth.cpp
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 17/12/2023.
//

#include "Synth.hpp"
#include "Oscillator.hpp"

Synth::Synth(float frequency, double amp, int voices) : amp(amp), frequency(frequency), voices(voices) {
    this->amp = amp;
    this->voices = voices;
    // create oscillators
    for (int i = 0; i < voices; i++) {
        oscillators.push_back(std::make_unique<Sine>());
    }
};

Synth::~Synth(){
    
}

double Synth::midiNoteToFrequency(int midiNote){
    return 440.0 * pow(2.0, (static_cast<double>(midiNote) - 69.0) / 12.0); // https://newt.phys.unsw.edu.au/jw/notes.html
};

void Synth::setSampleRate(float sampleRate){
    // store sample rate
    this->sampleRate = sampleRate;
    
    // set oscillator sample rates
    for(int i = 0; i < voices; i++){
        oscillators[i]->setSamplerate(sampleRate);
    }
}

void Synth::setAmp(double amp){
    this->amp = amp;
};

void Synth::setFrequency(float frequency){
    this->frequency = frequency;
    
    for(int i = 0; i < voices; i++){
        oscillators[i]->setFrequency(frequency);
    }
};

void Synth::setNote(int note){
    frequency = midiNoteToFrequency(note);
    setFrequency(frequency);
}

void Synth::setRatio(int ratio){
    
}

void Synth::setDepth(float depth){
    
}

float Synth::getSample(){
    return oscillators[0]->getSample() * amp;
}

float Synth::getPhase(){
    return phase;
}

double Synth::getAmp(){
    return amp;
}

float Synth::getFrequency(){
    return frequency;
}

std::string Synth::getOscillatorType(int oscillator){
    return oscillators[oscillator]->getOscillatorType();
}

void Synth::tick(){
    for(int i = 0; i < voices; i++){
        oscillators[i]->tick();
    }
    // update synth phase
    phase = oscillators[0]->getPhase();
}
