//
//  Melody.hpp
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 18/12/2023.
//

#ifndef Melody_hpp
#define Melody_hpp

#include <stdio.h>

#define NUM_NOTES 4
#define NUM_DURS 5

class Melody {
public:
    Melody();
    ~Melody();
    
    float getNote();
    float getDur();
    
private:
    float melody[NUM_NOTES] = {60, 64, 67, 71};
    float durations[NUM_DURS] = {400, 800, 400, 800, 200};
    int noteIndex;
    int durIndex;
};

#endif /* Melody_hpp */
