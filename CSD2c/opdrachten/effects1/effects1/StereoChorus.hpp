//
//  StereoChorus.hpp
//  effects1
//
//  Created by Vincent Van den Broeck on 23/02/2024.
//

#ifndef StereoChorus_hpp
#define StereoChorus_hpp

#include <stdio.h>
#include "Effect.hpp"
#include "CircBuffer.hpp"
#include "Oscillator.hpp"

class StereoChorus : public Effect {
private:
    float delaySamples;
    float offsetSamples;
    uint size, distance;
    CircBuffer l_buffer;
    CircBuffer r_buffer;
    CircBuffer * buffer[2];
    Sine * lfo[2];
    float applyEffect(int channel, float sample) override;
    
public:
    StereoChorus(float samplerate = 44100, float delay = 20, float maxDelay = 40) : Effect(), l_buffer(), r_buffer() {
        delaySamples = (delay / 1000.0f) * samplerate;
        offsetSamples = 0.02 * samplerate;
        size = (maxDelay / 1000.0f) * samplerate;
        l_buffer.resetSize(size);
        l_buffer.setDistanceRW(delaySamples);
        r_buffer.resetSize(size);
        r_buffer.setDistanceRW(delaySamples);
        buffer[0] = &l_buffer;
        buffer[1] = &r_buffer;
        lfo[0] = new Sine(0.2, 1, samplerate);
        lfo[1] = new Sine(0.2, 1, samplerate);
        lfo[1]->setPhase(0.3);
        }
    ~StereoChorus();
    void tick();
    uint getSize();
    uint getDistance();
};

#endif /* StereoChorus_hpp */
