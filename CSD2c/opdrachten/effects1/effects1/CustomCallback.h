//
//  CustomCallback.h
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 17/12/2023.
//

#ifndef CustomCallback_h
#define CustomCallback_h

#include "jack_module.h"
#include "Tremolo.hpp"
#include "Delay.hpp"
#include "Waveshaper.hpp"
#include "Oscillator.hpp"

class CustomCallback : public AudioCallback {
public:
    void prepare (int rate) override {
        // set values
        samplerate = (float) rate;
        tremolo.setSampleRate(rate);
        delay.setFeedback(0.5f);
    }
    
    ~CustomCallback(){
        AudioCallback::~AudioCallback();
    }
    
    // audio callback function
    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
        
        for (int channel = 0u; channel < numInputChannels; channel++) {
            for (int i = 0u; i < numFrames; i++) {
                buffer.outputChannels[channel][i] = waveshaper.process(buffer.inputChannels[channel][i]);
                
                tremolo.tick();
                delay.tick();
            }
        }
    }
    
private:
    float samplerate = 44100;
    // 5hz tremolo
    Tremolo tremolo = Tremolo(samplerate, 1.0f, 5.0f);
    
    // 0.5s delay
    Delay delay = Delay(samplerate, samplerate/2.0f);
    
    // Waveshaper
    Waveshaper waveshaper = Waveshaper(50.0f);
};

#endif /* CustomCallback_h */
