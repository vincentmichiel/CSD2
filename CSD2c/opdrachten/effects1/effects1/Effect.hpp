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
    bool bypass;
    float mix;
public:
    Effect(float mix = 1.0);
    virtual ~Effect();
    // setters
    void setMix(float mix);
    void setBypass(bool bypass);
    // methods
    float process(int channel, float sample);
    virtual float applyEffect(int channel, float sample) = 0;
};

#endif /* Effect_hpp */
