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

class MultitapDelay : public Effect {
private:
    uint size;
    CircBuffer circBuffer;
    float applyEffect(float sample) override;
    uint * distances;
    
public:
    MultitapDelay(float samplerate, uint size, uint * distances, uint tapAmount) : Effect(), size(size), circBuffer(), distances(distances) {
        circBuffer.resetSize(size * samplerate / 1000.0);
        for(int i = 0; i < tapAmount; i++){
            distances[i] = distances[i] * samplerate / 1000.0;
        }
        circBuffer.setTapAmount(tapAmount);
        circBuffer.setDistances(distances);
    }
    ~MultitapDelay();
    uint getSize();
    uint* getDistances();
    void tick();
};


#endif /* MultitapDelay_hpp */
