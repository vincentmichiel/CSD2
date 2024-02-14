//
//  Effect.hpp
//  effects1
//
//  Created by Vincent Van den Broeck on 08/02/2024.
//

#ifndef Effect_hpp
#define Effect_hpp

#include <stdio.h>

class Effect {
private:
    float mix;
public:
    Effect(float mix = 1.0);
    // setters
    void setMix(float mix);
    // methods
    float process(float sample);
    virtual float applyEffect(float sample) = 0;
};

#endif /* Effect_hpp */
