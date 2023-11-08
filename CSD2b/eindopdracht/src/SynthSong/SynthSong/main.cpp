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
    
    Triangle sine1;
    
    
    sine1.setAmp(0.05);
    sine1.start();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    sine1.stop();
    
    
    return 0;
} // main()
