//
//  instrument.hpp
//  instrument_class
//
//  Created by Vincent Van den Broeck on 01/11/2023.
//

#ifndef instrument_hpp
#define instrument_hpp

#include <stdio.h>
#include<iostream>

class Instrument {
private:
    std::string sSound;
    
public:
    Instrument(std::string sound);
    void play();
    void roll(int count);
};

#endif /* instrument_hpp */
