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
private:
    int ratio;
    float depth;
public:
    FMSynth(float frequency = 440, double amp = 1.0, int voices = 2);
    ~FMSynth();
    void tick() override;
    // setters
    void setOscillatorAmp(int voice, double amp) override;
    void setFrequency(float frequency) override;
    void setRatio(int ratio) override;
    void setDepth(float depth) override;
    // getters
    float getSample() override;
    int getRatio();
    float getDepth();
};

#endif /* FMSynth_hpp */
