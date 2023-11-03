//
//  instrument.hpp
//  instrument_inheritance
//
//  Created by Vincent Van den Broeck on 01/11/2023.
//

#ifndef instrument_hpp
#define instrument_hpp

#include <stdio.h>
#include<iostream>

class Instrument{
private:
    // generic attributes
    std::string sName;
    int pitchRange[2];
    std::string sSound;
    
public:
    // generic methods
    explicit Instrument(std::string name, int lowestPitch, int highestPitch, std::string sound);
    virtual bool play(int pitch);
};

class Keys : public Instrument {
private:
    bool sSustain;
    bool sUnaCorda;
public:
    using Instrument::Instrument;
    void play(int pitch, bool sustain, bool unaCorda);
};

class Strings : public Instrument {
private:
    double vDepth;
    double vSpeed;
public:
    using Instrument::Instrument;
    void play(int pitch, double vibratoDepth, double vibratoSpeed);
};

class Brass : public Instrument {
private:
    bool sFlutter;
public:
    using Instrument::Instrument;
    void play(int pitch, bool flutter);
};

#endif /* instrument_hpp */
