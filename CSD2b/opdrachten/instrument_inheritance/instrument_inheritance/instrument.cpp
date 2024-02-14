//
//  instrument.cpp
//  instrument_inheritance
//
//  Created by Vincent Van den Broeck on 01/11/2023.
//

#include "instrument.hpp"

Instrument::Instrument(std::string name, int lowestPitch, int highestPitch, std::string sound){
    // assign variables
    sName = name;
    pitchRange[0] = lowestPitch;
    pitchRange[1] = highestPitch;
    sSound = sound;
};

bool Instrument::play(int pitch){
    // check if pitch is within pitch range of instrument
    if(pitch >= pitchRange[0] && pitch <= pitchRange[1]){
        // play sound
        std::cout << sName << " is playing note " << pitch << std::endl;
        std::cout << sSound << std::endl;
        // go to instrument specific play function
        return true;
    }
    // pitch out of range
    std::cout << "Pitch out of range for instrument " << sName << std::endl;
    return false;
};

void Keys::play(int pitch, bool sustain, bool unaCorda){
    if(Instrument::play(pitch)){ // check if pitch is within pitch range and play sound
        // pedals
        sSustain = sustain;
        sUnaCorda = unaCorda;
        std::cout << "Sustain: " << sSustain << std::endl << "Una Corda: " << sUnaCorda << std::endl;
    }
};

void Strings::play(int pitch, double vibratoDepth, double vibratoSpeed){
    if(Instrument::play(pitch)){ // check if pitch is within pitch range and play sound
        // vibrato
        vDepth = vibratoDepth;
        vSpeed = vibratoSpeed;
        std::cout << "Vibrato Amount: " << vDepth << std::endl << "Vibrato Speed: " << vSpeed << "hz" << std::endl;
    }
};

void Brass::play(int pitch, bool flutter){
    if(Instrument::play(pitch)){ // check if pitch is within pitch range and play sound
        // fluttertongue
        sFlutter = flutter;
        std::cout << "Fluttertongue: " << sFlutter << std::endl;
    }
};

