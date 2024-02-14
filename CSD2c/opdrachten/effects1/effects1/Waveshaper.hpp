//
//  Waveshaper.hpp
//  effects1
//
//  Created by Vincent Van den Broeck on 13/02/2024.
//

#ifndef Waveshaper_hpp
#define Waveshaper_hpp

#include <stdio.h>
#include "Effect.hpp"

class Waveshaper : public Effect {
public:
    Waveshaper(float ratio = 2) : Effect(), ratio(ratio){};
    void setRatio(float ratio);
private:
    float ratio;
    float applyEffect(float sample) override;
};

#endif /* Waveshaper_hpp */
