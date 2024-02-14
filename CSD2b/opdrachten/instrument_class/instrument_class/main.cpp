//
//  main.cpp
//  instrument_class
//
//  Created by Vincent Van den Broeck on 01/11/2023.
//

#include <iostream>
#include "instrument.hpp"

int main(int argc, const char * argv[]) {
    Instrument instrument1("Ratatataaa");
    Instrument instrument2("Fweeeep");
    
    instrument1.roll(4);
    instrument2.play();
    return 0;
}
