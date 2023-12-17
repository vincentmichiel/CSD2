//
//  FMSynth.hpp
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 17/12/2023.
//

#ifndef FMSynth_hpp
#define FMSynth_hpp

#include <stdio.h>
#include "Synth.hpp"

class FMSynth : public Synth {
public:
    FMSynth(double amp = 1.0, int voices = 2);
    ~FMSynth();
    // setters
    void setOscillatorAmp(int voice, double amp) override;
    // getters
    float getSample() override;
};

#endif /* FMSynth_hpp */
