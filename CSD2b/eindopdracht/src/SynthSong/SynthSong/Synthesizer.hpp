//
//  Synthesizer.hpp
//  SynthSong
//
//  Created by Vincent Van den Broeck on 09/11/2023.
//

#ifndef Synthesizer_hpp
#define Synthesizer_hpp

#include <stdio.h>
#include <vector>
#include <memory>
#include <thread>
#include "Oscillator.hpp"

class Synthesizer {
private:
    double amp;
    // adsr values
    std::vector<int> adsr;
    int voices;
    // array of oscillators
    std::vector<std::unique_ptr<Oscillator>> oscillators;
    double midiNoteToFrequency(int midiNote);
    
public:
    Synthesizer(double initialAmp = 0.5, const std::vector<int>& initialAdsr = {1, 1, 90, 10}, int initialVoices = 1);
    ~Synthesizer();
    void changeOscillatorType(OscillatorType newType);
    void setAmp(double newAmp);
    void playNote(int midiNote, double amplitude, int duration);
    std::thread oscillatorThread;
};

#endif /* Synthesizer_hpp */
