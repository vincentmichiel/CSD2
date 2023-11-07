//
//  main.cpp
//  SynthSong
//
//  Created by Vincent Van den Broeck on 05/11/2023.
//
#include <iostream>
#include "audio_io.hpp"
#include "Constants.hpp"
#include "Oscillator.hpp"

using namespace std;


#define NUM_SECONDS        1

int output_device = 0;



int main(int argc,char** argv)
{
    // set output device
    Audio_IO audiostream;
    audiostream.initialise();
    audiostream.list_devices();
    cout << "Give output device number: ";
    cin >> output_device;
    audiostream.terminate();
    
    Sine sine;
    sine.setFreq(880);
    sine.start();
    
    return 0;
} // main()

