//
//  CustomCallback.h
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 17/12/2023.
//

#ifndef CustomCallback_h
#define CustomCallback_h

#include "jack_module.h"
#include "Reverb.hpp"

class CustomCallback : public AudioCallback {
public:
    void prepare (int rate) override {
        // set values
        samplerate = (float) rate;
    }
    
    ~CustomCallback(){
        delete reverb;
        AudioCallback::~AudioCallback();
    }
    
    // audio callback function
    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
        
        for (int i = 0u; i < numFrames; i++) {
            for (int channel = 0u; channel < numOutputChannels; channel++) {
                buffer.outputChannels[channel][i] = reverb->process(buffer.inputChannels[0][i], channel);
            }
            // ticks
            reverb->tick();
        }
        
    }
    
private:
    float samplerate = 44100;
    Reverb * reverb = new Reverb(samplerate, 0.4);
};

#endif /* CustomCallback_h */
