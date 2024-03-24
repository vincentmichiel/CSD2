//
//  MultitapDelay.hpp
//  Autoverb
//
//  Created by Vincent Van den Broeck on 22/03/2024.
//

#ifndef MultitapDelay_hpp
#define MultitapDelay_hpp

#include <stdio.h>
#include <iostream>
#include "Effect.hpp"
#include "CircBuffer.hpp"

struct doubleOutput {
    float multiOut[2];
};

class MultitapDelay : public Effect {
private:
    uint size, tapAmount;
    CircBuffer circBuffer;
    uint * distances;
    
public:
    MultitapDelay(float samplerate, uint size, uint * distances, uint tapAmount) : Effect(), size(size), tapAmount(tapAmount), circBuffer(), distances(distances) {
        circBuffer.resetSize(size * samplerate / 1000.0);
        for(int i = 0; i < tapAmount; i++){
            distances[i] = distances[i] * samplerate / 1000.0;
        }
        circBuffer.setTapAmount(tapAmount);
        circBuffer.setDistances(distances);
    }
    ~MultitapDelay();
    float readTap(int tap);
    uint getSize();
    uint* getDistances();
    doubleOutput applyEffectDouble(float sample);
    void tick();
};


#endif /* MultitapDelay_hpp */
