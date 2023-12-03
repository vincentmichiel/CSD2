//
//  Synthesizer.cpp
//  SynthSong
//
//  Created by Vincent Van den Broeck on 09/11/2023.
//

#include "Synthesizer.hpp"
#include <vector>
#include <thread>
#include <chrono>
#include <future>


Synthesizer::Synthesizer(double initialAmp, const std::vector<int>& initialAdsr, int initialVoices) : amp(initialAmp), adsr(initialAdsr), voices(initialVoices) {
    // create oscillators
    for (int i = 0; i < voices; i++) {
        oscillators.push_back(std::make_unique<Sine>());
    }
};

Synthesizer::~Synthesizer(){
    // delete synth
};

double Synthesizer::midiNoteToFrequency(int midiNote){
    return 440.0 * pow(2.0, (static_cast<double>(midiNote) - 69.0) / 12.0); // https://newt.phys.unsw.edu.au/jw/notes.html
};

void Synthesizer::changeOscillatorType(OscillatorType newType) {
    // clear existing oscillators
    oscillators.clear();
    
    // create new oscillator based on the selected type
    switch (newType) {
        case OscillatorType::Sine:
            oscillators.push_back(std::make_unique<Sine>());
            break;
        case OscillatorType::Square:
            oscillators.push_back(std::make_unique<Square>());
            break;
        case OscillatorType::Triangle:
            oscillators.push_back(std::make_unique<Triangle>());
            break;
        case OscillatorType::Noise:
            oscillators.push_back(std::make_unique<Noise>());
            break;
        default:
            // type not found, add sine
            oscillators.push_back(std::make_unique<Sine>());
            break;
    }
}

void Synthesizer::setAmp(double newAmp){
    amp = newAmp;
};

void Synthesizer::playNote(int midiNote = 60, double amplitude = 0.5, int duration = 500) {
    // calculate the duration of one sample in seconds
    double sampleDuration = 1.0 / SAMPLERATE;
    // calculate the number of steps based on adsr times
    int attackDuration = static_cast<int>((adsr[0]) * SAMPLERATE/1000);
    int decayDuration = static_cast<int>(adsr[1] * SAMPLERATE / 1000);
    int releaseDuration = static_cast<int>(adsr[3] * SAMPLERATE / 1000);
    int sustainDuration = duration - (attackDuration + decayDuration + releaseDuration * static_cast<int>(sampleDuration));
    
    
    
    oscillators[0]->setFreq(midiNoteToFrequency(midiNote));
    oscillators[0]->setAmp(0);
    oscillators[0]->start();
    
    // run the sleep and stop in a separate thread
    oscillatorThread = std::thread([this, duration, attackDuration, decayDuration, sustainDuration, releaseDuration, amplitude, sampleDuration] {
        // attack phase
        for (int i = 0; i < attackDuration; i++) {
            double progress = static_cast<double>(i) / attackDuration;
            oscillators[0]->setAmp(progress * amplitude * amp);
            // Sleep for one sample duration
            std::this_thread::sleep_for(std::chrono::duration<double>(sampleDuration));
        }
        
        // attack finished
        oscillators[0]->setAmp(amp * amplitude);
    
        // decay Phase
        float sustainReverse = (float)(100 - adsr[2]) / 100;
        std::cout << sustainReverse << std::endl;
        for (int i = 0; i < decayDuration; i++) {
            double progress = static_cast<double>(i) / decayDuration;
            oscillators[0]->setAmp((1 - progress * sustainReverse) * amplitude * amp);
            // Sleep for one sample duration
            std::this_thread::sleep_for(std::chrono::duration<double>(sampleDuration));
        }
        
        // sustain phase
        
        
        std::cout << oscillators[0]->getAmp() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        
        
        oscillators[0]->stop();
    });
};
