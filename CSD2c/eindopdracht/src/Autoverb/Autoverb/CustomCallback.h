//
//  CustomCallback.h
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 17/12/2023.
//

#ifndef CustomCallback_h
#define CustomCallback_h

#include "jack_module.h"
#include "Delay.hpp"
#include "MultitapDelay.hpp"
#include "Moddelay.hpp"
#include "AllpassFilter.hpp"

class CustomCallback : public AudioCallback {
public:
    void prepare (int rate) override {
        // set values
        samplerate = (float) rate;
    }
    
    ~CustomCallback(){
        AudioCallback::~AudioCallback();
    }
    
    // audio callback function
    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
        
        for (int i = 0u; i < numFrames; i++) {
            for (int channel = 0u; channel < numOutputChannels; channel++) {
                buffer.outputChannels[channel][i] = buffer.inputChannels[0][i];
            }
            // ticks
        }
        
    }
    
private:
    float samplerate = 44100;
};

#endif /* CustomCallback_h */
