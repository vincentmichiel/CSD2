//
//  main.cpp
//  effects1
//
//  Created by Vincent Van den Broeck on 08/02/2024.
//

#include <iostream>
#include <fstream>
#include "CustomCallback.h"
#include "UI.hpp"
#include "deltasequence.h"
#include "Filters.h"

#define BYPASS_AUDIO_LOOP 0

int main(int argc, const char * argv[]) {
    // init audio
    CustomCallback callback = CustomCallback {};
    JackModule jackModule = JackModule { callback };
    
#if BYPASS_AUDIO_LOOP
    Biquad filter;
    filter.setCoefficients(0.029587210720909994,
                           0,
                           -0.029587210720909994,
                           -1.9254521965128737,
                           0.9408255785581799);
    
    
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
        
        for(int i = 0; i < 0.5 * samplerate; i++){
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
    // user input
    bool enableTremolo = true, enableDelay = true, enableWaveshaper = true;
    float tremoloMix = 0.0f, delayMix = 0.0f, waveshaperMix = 0.0f;
    float tremoloFrequency = 1.0f;
    float tremoloDepth = 0.0f;
    float delaySeconds = 0.0f;
    float delayFeedback = 0.0f;
    float waveshaperDrive = 0.0f;
    
//    enableTremolo = UI::getYesNo("Enable tremolo?");
//    if(enableTremolo){
//        tremoloMix = UI::getFloat("Set the tremolo mix: ", 0.0f, 1.0f);
//        tremoloFrequency = UI::getFloat("Set the tremolo frequency: ", 0.1f, 100.0f);
//        tremoloDepth = UI::getFloat("Set the tremolo depth: ", 0.0f, 1.0f);
//    }
//    
//    enableDelay = UI::getYesNo("Enable delay?");
//    if(enableDelay){
//        delayMix = UI::getFloat("Set the delay mix: ", 0.0f, 1.0f);
//        delaySeconds = UI::getFloat("How many seconds delay?", 0.1, 10.0f);
//        delayFeedback = UI::getFloat("Set delay feedback: ", 0.0f, 0.99f);
//    }
//    
//    enableWaveshaper = UI::getYesNo("Enable waveshaper?");
//    if(enableWaveshaper){
//        waveshaperMix = UI::getFloat("Set the waveshaper mix: ", 0.0f, 1.0f);
//        waveshaperDrive = UI::getFloat("Set the waveshaper drive: ", 0.0f, 50.0f);
//    }
    
    callback.setEffects(enableTremolo, enableDelay, enableWaveshaper, tremoloMix, delayMix, waveshaperMix, tremoloFrequency, tremoloDepth, delaySeconds, delayFeedback, waveshaperDrive);
    
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
