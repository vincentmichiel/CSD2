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
#include "Synthesizer.hpp"

int output_device = 0;

int main(int argc,char** argv)
{
    // set output device
    Audio_IO audiostream;
    audiostream.initialise();
    audiostream.list_devices();
    std::cout << "Give output device number: ";
    std::cin >> output_device;
    audiostream.terminate();
    
    Synthesizer synth;
    synth.setAmp(1);
    synth.playNote(60, 0.5, 2000);
    std::cout << "main" << std::endl;
    
    // close audio thread
    if (synth.oscillatorThread.joinable()) {
        synth.oscillatorThread.join();  // Wait for the audio thread to complete
    }
    return 0;
} // main()
