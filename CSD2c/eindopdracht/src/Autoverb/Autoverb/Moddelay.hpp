//
//  Moddelay.hpp
//  Autoverb
//
//  Created by Vincent Van den Broeck on 22/03/2024.
//

#ifndef Moddelay_hpp
#define Moddelay_hpp

#include <stdio.h>
#include "Effect.hpp"
#include "CircBuffer.hpp"
#include "Oscillator.hpp"

class Moddelay : public Effect {
private:
    uint size, start, end;
    float feedback;
    CircBuffer circBuffer;
    float applyEffect(float sample) override;
    Sine LFO;
public:
    Moddelay(float samplerate = 44100, uint size = 100, uint start = 50, uint end = 100, float modSpeed = 1.0, float feedback = 0) : Effect(), size(size), start(start), end(end),  feedback(feedback), circBuffer(), LFO(modSpeed, 1, samplerate) {
        this->start = start * samplerate / 1000.0;
        this->end = end * samplerate / 1000.0;
        circBuffer.resetSize(size * samplerate / 1000.0);
        circBuffer.setDistanceRW(this->start);
        }
    ~Moddelay();
    void setFeedback(float feedback);
    uint getSize();
    float getFeedback();
    void tick();
};

#endif /* Moddelay_hpp */
