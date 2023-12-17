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

class CustomCallback : public AudioCallback {
public:
    void prepare (int rate) override {
        samplerate = (float) rate;
        synth->setSampleRate(samplerate);
        
        synth->setOscillatorAmp(0, 1.0);
        synth->setOscillatorAmp(1, 0.3);
        synth->setOscillatorAmp(2, 0.1);
    }
    
    ~CustomCallback(){
        AudioCallback::~AudioCallback();
        delete synth;
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
               
            buffer.outputChannels[0][i] = sample;
            
            // write to text file
            outfile << synth->getPhase() + phaseCycle << ":" << sample << std::endl;
            
            synth->tick();
        }
        // close text file
        outfile.close();
    }

private:
    float samplerate = 44100;
    Synth * synth = new AnalogSynth;
};

#endif /* CustomCallback_h */
