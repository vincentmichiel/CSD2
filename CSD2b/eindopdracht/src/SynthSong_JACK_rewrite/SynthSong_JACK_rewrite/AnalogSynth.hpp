//
//  AnalogSynth.hpp
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 17/12/2023.
//

#ifndef AnalogSynth_hpp
#define AnalogSynth_hpp

#include <stdio.h>
#include "Synth.hpp"

class AnalogSynth : public Synth {
public:
    AnalogSynth(float frequency = 440, double amp = 1.0, int voices = 3);
    ~AnalogSynth();
    // setters
    void setOscillatorAmp(int voice, double amp) override;
    // getters
    float getSample() override;
};

#endif /* AnalogSynth_hpp */
