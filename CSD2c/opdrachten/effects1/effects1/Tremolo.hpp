//
//  Tremolo.hpp
//  effects1
//
//  Created by Vincent Van den Broeck on 08/02/2024.
//

#ifndef Tremolo_hpp
#define Tremolo_hpp

#include <stdio.h>
#include "Effect.hpp"
#include "Oscillator.hpp"

class Tremolo : public Effect {
private:
    float depth;
    float frequency;
    Sine LFO;
    float applyEffect(float sample) override;
    
public:
    Tremolo(float sampleRate = 44100, float depth = 1, float frequency = 20) : Effect(), depth(depth), frequency(frequency), LFO() {
        LFO.setFrequency(frequency);
        LFO.setSamplerate(sampleRate);
        }
    ~Tremolo();
    
    void tick();
    void setSampleRate(float sampleRate);
    void setDepth(float depth);
    void setFrequency(float frequency);
    float getDepth();
    float getFrequency();
};

#endif /* Tremolo_hpp */
