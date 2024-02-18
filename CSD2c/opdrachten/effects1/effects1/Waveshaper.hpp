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

#define BUFFER_SIZE 1024

class Waveshaper : public Effect {
public:
    Waveshaper(float drive = 2);
    void setDrive(float ratio);
    void plot();
private:
    float wavetable[BUFFER_SIZE];
    float drive;
    float applyEffect(float sample) override;
};

#endif /* Waveshaper_hpp */
