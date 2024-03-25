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
protected:
    bool bypass;
    float mix;
    
    
public:
    Effect(float mix = 1.0);
    virtual ~Effect();
    // setters
    void setMix(float mix);
    void setBypass(bool bypass);
    // methods
    float process(float sample = 0.0f, int channel = - 1);
    virtual float applyEffect(float sample);
    virtual float applyEffect(int channel, float sample);
};

#endif /* Effect_hpp */
