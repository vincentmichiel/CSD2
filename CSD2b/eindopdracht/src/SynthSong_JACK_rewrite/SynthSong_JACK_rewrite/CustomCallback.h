//
//  CustomCallback.h
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 17/12/2023.
//

#ifndef CustomCallback_h
#define CustomCallback_h

#include "jack_module.h"
#include "Oscillator.hpp"
#include "Synth.hpp"
#include "AnalogSynth.hpp"
#include "FMSynth.hpp"
#include<iostream>
#include <vector>

class CustomCallback : public AudioCallback {
public:
    void prepare (int rate) override {
        samplerate = (float) rate;
        
        synths.push_back(std::make_unique<AnalogSynth>());
        synths.push_back(std::make_unique<FMSynth>());
        
        for(int i = 0; i < 2; i++){
            synths[i]->setSampleRate(samplerate);
        }
        
        synths[0]->setOscillatorAmp(0, 1.0);
        synths[0]->setOscillatorAmp(1, 0.3);
        synths[0]->setOscillatorAmp(2, 0.1);
    }
    
    ~CustomCallback(){
        AudioCallback::~AudioCallback();
    }

    // audio callback function
    void process (AudioBuffer buffer) override {
        // open text file
        std::ofstream outfile;
        outfile.open("waveform.txt");
        float phaseCycle = 0.0;
        
        for (int i = 0; i < buffer.numFrames; ++i) {
            // calculate sample and write to audio buffer
            float sample = synths[0]->getSample();
               
            buffer.outputChannels[0][i] = sample;
            
            // write to text file
            outfile << synths[1]->getPhase() + phaseCycle << ":" << sample << std::endl;
            
            for(int i = 0; i < 2; i++){
                synths[i]->tick();
            }
        }
        // close text file
        outfile.close();
    }

private:
    float samplerate = 44100;
    std::vector<std::unique_ptr<Synth>> synths;
};

#endif /* CustomCallback_h */
