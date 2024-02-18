//
//  main.cpp
//  effects1
//
//  Created by Vincent Van den Broeck on 08/02/2024.
//

#include <iostream>
#include <fstream>
#include "CustomCallback.h"
#include "WavetableGenerator.hpp"

#define BYPASS_AUDIO_LOOP 0

#define BUFFER_SIZE 1024

int main(int argc, const char * argv[]) {
    // init audio
    CustomCallback callback = CustomCallback {};
    JackModule jackModule = JackModule { callback };
    
#if BYPASS_AUDIO_LOOP
    // generate wavetable and fill with sine waveform
    float wavetable[BUFFER_SIZE];
    WavetableGenerator::generateWaveform(wavetable, BUFFER_SIZE,
                                         WavetableGenerator::WaveformType::SINE);
    
    // clear plot file
    std::ofstream ofs;
    ofs.open("waveform.txt", std::ofstream::out | std::ofstream::trunc);
    
    // write to file
    for(int i = 0; i < BUFFER_SIZE; i++){
        ofs << i << ":" << wavetable[i] << std::endl;
    }
    
    // close file
    ofs.close();

#else
    jackModule.init(1, 1);
    
    bool running = true;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
        }
    }
#endif
    
    return 0;
}
