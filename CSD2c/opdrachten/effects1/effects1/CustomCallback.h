//
//  CustomCallback.h
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 17/12/2023.
//

#ifndef CustomCallback_h
#define CustomCallback_h

#include <iostream>
#include "jack_module.h"
#include "Tremolo.hpp"
#include "Delay.hpp"
#include "Waveshaper.hpp"
#include "StereoChorus.hpp"
#include "Oscillator.hpp"
#include "Filters.h"

class CustomCallback : public AudioCallback {
public:
    void prepare (int rate) override {
        // set values
        samplerate = (float) rate;
        tremolo->setSampleRate(rate);
        chorus = new StereoChorus;
        
        filter->setBCoefficient(0.99);
        filter->setA1Coefficient(0.2);
        filter->setA2Coefficient(0.3);
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
        delete chorus;
    }
    
    // audio callback function
    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
        
        for (int i = 0u; i < numFrames; i++) {
            for (int channel = 0u; channel < numOutputChannels; channel++) {
                buffer.outputChannels[channel][i] = filter->process(saw1.getSample());
            }
            
            saw1.tick();
            tremolo->tick();
            delay->tick();
            chorus->tick();
        }
        
    }
    
private:
    float samplerate = 44100;
    Saw saw1 = Saw(440, 1, samplerate);
    Tremolo * tremolo;
    Delay * delay;
    Waveshaper * waveshaper;
    StereoChorus * chorus;
    HalfBiquad * filter = new HalfBiquad;
};

#endif /* CustomCallback_h */
