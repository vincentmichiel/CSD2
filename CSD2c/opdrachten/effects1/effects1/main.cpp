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

#define BYPASS_AUDIO_LOOP 0

int main(int argc, const char * argv[]) {
    UI ui;
    // init audio
    CustomCallback callback = CustomCallback {};
    JackModule jackModule = JackModule { callback };
    
#if BYPASS_AUDIO_LOOP
   

#else
    // user input
    bool enableTremolo = true, enableDelay = true, enableWaveshaper = true;
    float tremoloMix = 0.0f, delayMix = 0.0f, waveshaperMix = 0.0f;
    float tremoloFrequency = 1.0f;
    float tremoloDepth = 0.0f;
    float delaySeconds = 0.0f;
    float delayFeedback = 0.0f;
    float waveshaperDrive = 0.0f;
    
    enableTremolo = ui.getYesNo("Enable tremolo?");
    if(enableTremolo){
        tremoloMix = ui.getFloat("Set the tremolo mix: ", 0.0f, 1.0f);
        tremoloFrequency = ui.getFloat("Set the tremolo frequency: ", 0.1f, 100.0f);
        tremoloDepth = ui.getFloat("Set the tremolo depth: ", 0.0f, 1.0f);
    }
    
    enableDelay = ui.getYesNo("Enable delay?");
    if(enableDelay){
        delayMix = ui.getFloat("Set the delay mix: ", 0.0f, 1.0f);
        delaySeconds = ui.getFloat("How many seconds delay?", 0.1, 10.0f);
        delayFeedback = ui.getFloat("Set delay feedback: ", 0.0f, 0.99f);
    }
    
    enableWaveshaper = ui.getYesNo("Enable waveshaper?");
    if(enableWaveshaper){
        waveshaperMix = ui.getFloat("Set the waveshaper mix: ", 0.0f, 1.0f);
        waveshaperDrive = ui.getFloat("Set the waveshaper drive: ", 0.0f, 50.0f);
    }
    
    callback.setEffects(enableTremolo, enableDelay, enableWaveshaper, tremoloMix, delayMix, waveshaperMix, tremoloFrequency, tremoloDepth, delaySeconds, delayFeedback, waveshaperDrive);
    
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
