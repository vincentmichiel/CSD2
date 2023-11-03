//
//  instrument.cpp
//  instrument_class
//
//  Created by Vincent Van den Broeck on 01/11/2023.
//

#include "instrument.hpp"
#include<iostream>

Instrument::Instrument(std::string sound){
    sSound = sound;
};

void Instrument::play(){
    std::cout << sSound << std::endl;
};

void Instrument::roll(int count){
    for(int i = 0; i < count; i++){
        play();
    }
}
