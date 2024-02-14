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
#include "FMSynth.hpp"
#include<iostream>
#include <vector>

class CustomCallback : public AudioCallback {
public:
    void setAmp(int newAmp){
        this->amp = (float) newAmp / 100.0;
    }
    void setDepth(int newDepth){
        this->depth = (float) newDepth / 100.0;
        synth->setDepth(this->depth);
    }
    void setFrequency(float newFrequency){
        this->note = newFrequency;
        synth->setNote(this->note);
        std::cout << synth->getFrequency() << std::endl;
    }
    
    void prepare (int rate) override {
        // set values
        samplerate = (float) rate;
        
        synth->setSampleRate(samplerate);
        synth->setAmp(1.0);
        synth->setRatio(2);
        
        // TESTING
        this->amp = 1.0;
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
            float sample = synth->getSample();
               
            buffer.outputChannels[0][i] = sample * this->amp;
            
            // write to text file
            outfile << synth->getPhase() + phaseCycle << ":" << sample << std::endl;
            
           
            synth->tick();
            
        }
        // close text file
        outfile.close();
    }

private:
    float amp;
    float depth;
    int note;
    FMSynth * synth = new FMSynth;
    float samplerate = 44100;
};

#endif /* CustomCallback_h */
