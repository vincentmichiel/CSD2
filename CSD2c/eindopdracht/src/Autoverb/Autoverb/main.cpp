//
//  main.cpp
//  Autoverb
//
//  Created by Vincent Van den Broeck on 22/03/2024.
//

#include <iostream>
#include <fstream>
#include "CustomCallback.h"
#include "Filters.h"

#define BYPASS_AUDIO_LOOP 1

int main(int argc, const char * argv[]) {
    // init audio
    CustomCallback callback = CustomCallback {};
    JackModule jackModule = JackModule { callback };
    
#if BYPASS_AUDIO_LOOP
    Biquad filter;
    filter.setCoefficients(0.8738265605660307,
                           -1.7476531211320614,
                           0.8738265605660307,
                           -1.7444563651686795,
                           0.7508498770954435);
    
    
    float samplerate = 44100;
    double freq = 0;
    double x;
    double max = 0;
    
    // plot
    // clear plot file
    std::ofstream ofs;
    ofs.open("waveform.txt", std::ofstream::out | std::ofstream::trunc);
    
    for(int j = 0; j < 0.5 * samplerate; j++){
        filter.clear();
        freq = j;
        max = 0;
        
        for(int i = 0; i < 0.25 * samplerate; i++){
            x = sin(freq * (2 * M_PI) * i / samplerate);
            x = filter.process(x);
            x = abs(x);
            
            if(x > max){
                max = x;
            }
        }
        // write to text file
        ofs << j << ":" << max << std::endl;
    }
    
    ofs.close();
    
#else
    
    jackModule.init(1, 2);
    
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
