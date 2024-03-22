//
//  Delay.hpp
//  effects1
//
//  Created by Vincent Van den Broeck on 08/02/2024.
//

#ifndef Delay_hpp
#define Delay_hpp

#include <stdio.h>
#include "Effect.hpp"
#include "CircBuffer.hpp"

class Delay : public Effect {
private:
    uint size, distance;
    float feedback;
    CircBuffer circBuffer;
    float applyEffect(float sample) override;
public:
    Delay(float samplerate = 44100, uint size = 100, uint distance = 100, float feedback = 0) : Effect(), size(size), distance(distance), feedback(feedback), circBuffer() {
        circBuffer.resetSize(size * samplerate / 1000.0);
        circBuffer.setDistanceRW(distance * samplerate / 1000.0);
        }
    ~Delay();
    void setFeedback(float feedback);
    uint getSize();
    uint getDistance();
    float getFeedback();
    void tick();
};

#endif /* Delay_hpp */
