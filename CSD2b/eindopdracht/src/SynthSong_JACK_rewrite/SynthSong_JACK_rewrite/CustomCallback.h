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
#include "UI.hpp"

class CustomCallback : public AudioCallback {
public:
    std::vector<std::unique_ptr<Synth>> synths;
    
    void customInit(int synthSelection){
        this->synthSelection = synthSelection;
    }
    
    void prepare (int rate) override {
        // set values
        samplerate = (float) rate;
        
        // create synths
        synths.push_back(std::make_unique<AnalogSynth>());
        synths.push_back(std::make_unique<FMSynth>());
        
        for(int i = 0; i < 2; i++){
            synths[i]->setSampleRate(samplerate);
            synths[i]->setAmp(0.0);
        }
        
        // analog
        synths[0]->setOscillatorAmp(0, 0.1);
        synths[0]->setOscillatorAmp(1, 0.3);
        synths[0]->setOscillatorAmp(2, 0.9);
        
        // fm
        synths[1]->setRatio(2);
        synths[1]->setDepth(0.2);
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
            float sample = synths[synthSelection]->getSample();
               
            buffer.outputChannels[0][i] = sample;
            
            // write to text file
            outfile << synths[synthSelection]->getPhase() + phaseCycle << ":" << sample << std::endl;
            
            for(int i = 0; i < 2; i++){
                synths[i]->tick();
            }
        }
        // close text file
        outfile.close();
    }

private:
    float samplerate = 44100;
    int synthSelection;
};

#endif /* CustomCallback_h */
