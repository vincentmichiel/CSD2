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
        tremolo->setSampleRate(rate);
        
    }
    
    void setEffects(bool enableTremolo, bool enableDelay, bool enableWaveshaper, float tremoloMix, float delayMix, float waveshaperMix, float tremoloFrequency, float tremoloDepth, float delaySeconds, float delayFeedback, float waveshaperDrive){
        // tremolo
        tremolo = new Tremolo(samplerate, tremoloDepth, tremoloFrequency);
        tremolo->setMix(tremoloMix);
        tremolo->setBypass(!enableTremolo);
        
        // delay
        delay = new Delay(samplerate * delaySeconds, samplerate * delaySeconds);
        delay->setFeedback(delaySeconds);
        delay->setMix(delayMix);
        delay->setBypass(!enableDelay);
        
        // waveshaper
        waveshaper = new Waveshaper(waveshaperDrive);
        waveshaper->setMix(waveshaperMix);
        waveshaper->setBypass(!enableWaveshaper);
    }
    
    ~CustomCallback(){
        AudioCallback::~AudioCallback();
        delete tremolo;
        delete delay;
        delete waveshaper;
    }
    
    // audio callback function
    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
        
        for (int channel = 0u; channel < numInputChannels; channel++) {
            for (int i = 0u; i < numFrames; i++) {
                buffer.outputChannels[channel][i] = tremolo->process(delay->process(waveshaper->process(buffer.inputChannels[channel][i])));
                
                tremolo->tick();
                delay->tick();
            }
        }
    }
    
private:
    float samplerate = 44100;
    
    Tremolo * tremolo;
    Delay * delay;
    Waveshaper * waveshaper;
};

#endif /* CustomCallback_h */
