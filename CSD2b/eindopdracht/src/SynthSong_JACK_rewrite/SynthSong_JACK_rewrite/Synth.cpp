//
//  Synth.cpp
//  SynthSong_JACK_rewrite
//
//  Created by Vincent Van den Broeck on 17/12/2023.
//

#include "Synth.hpp"
#include<iostream>

Synth::Synth(){
    std::cout << "synth created" << std::endl;
}

Synth::~Synth(){
    std::cout << "synth removed" << std::endl;
}
