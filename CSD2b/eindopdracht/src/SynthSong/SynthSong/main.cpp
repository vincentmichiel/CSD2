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
    
    Sine sine1;
    Sine sine2;
    Sine sine3;
    
    sine1.setFreq(440);
    sine2.setFreq(523.25);
    sine3.setFreq(659.25);
    
    sine1.setAmp(0.2);
    sine2.setAmp(0.2);
    sine3.setAmp(0.2);
    
    sine1.start();
    sine2.start();
    sine3.start();
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    sine1.stop();
    sine2.stop();
    sine3.stop();
    
    
    return 0;
} // main()

