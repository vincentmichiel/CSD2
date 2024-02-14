//
//  main.cpp
//  instrument_inheritance
//
//  Created by Vincent Van den Broeck on 01/11/2023.
//

#include <iostream>
#include "instrument.hpp"

int main(int argc, const char * argv[]) {
    // create instruments
    Keys piano("Piano", 0, 87, "ploink");
    Strings violin("Violin", 55, 103, "fweee");
    Brass trumpet("Trumpet", 55, 82, "pweeeepp");
    
    // play instruments
    piano.play(60, true, false);
    violin.play(94, 0.8, 5.2);
    trumpet.play(72, false);
    
    return 0;
};
