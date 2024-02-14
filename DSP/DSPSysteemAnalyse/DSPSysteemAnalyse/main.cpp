//
//  main.cpp
//  DSPSysteemAnalyse
//
//  Created by Vincent Van den Broeck on 08/02/2024.
//

#include <iostream>
#include <math.h>
#include <fstream>
#include "Fir.hpp"

int main(int argc, const char * argv[]) {
    LowPass lpf;
    HighPass hpf;
    float sampleRate = 48000.0;
    double freq = 0;
    double x;
    double max = 0;
    
    // clear plot file
    std::ofstream ofs;
    ofs.open("waveform.txt", std::ofstream::out | std::ofstream::trunc);
   
    
    for(int j = 0; j < 0.5 * sampleRate; j++){
        lpf.clear();
        hpf.clear();
        freq = j;
        max = 0;
        
        for(int i = 0; i < sampleRate/2; i++){
            x = sin(freq * (2 * M_PI) * i / sampleRate);
            x = hpf.process(x);
            x = abs(x);
            
            if(x > max){
                max = x;
            }
        }
        // write to text file
        ofs << j << ":" << max << std::endl;
    }
    
    int n;
    lpf.clear();
    hpf.clear();
    for(int i = -3; i < 14; i++){
        if(i == 0){
            n = 1;
        } else {
            n = 0;
        }
        std::cout << i << ": " << hpf.process(n) << std::endl;
    }
    
    
    ofs.close();
    
    return 0;
}
