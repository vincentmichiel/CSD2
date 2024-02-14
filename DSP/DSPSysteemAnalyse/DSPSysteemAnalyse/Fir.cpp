//
//  Fir.cpp
//  DSPSysteemAnalyse
//
//  Created by Vincent Van den Broeck on 11/02/2024.
//

#include "Fir.hpp"
#include <iostream>

Fir::Fir(){
    bufferSize = 3;
    buffer = (double*)malloc(bufferSize * sizeof(double));
    memset(buffer, 0.0, bufferSize * sizeof(double));
}

Fir::~Fir(){
    free(buffer);
}

void Fir::clear(){
    memset(buffer, 0.0, bufferSize * sizeof(double));
}

double LowPass::process(double x){
    // store new value
    buffer[1] = x;
    
    // fir
    y = 0.5 * buffer[1] + 0.5 * buffer[0];
    
    // store value in buffer
    buffer[0] = buffer[1];
    return y;
}

double HighPass::process(double x){
    // update buffer
    for(int i = bufferSize - 1; i > 0; i--){
        buffer[i] = buffer[i - 1];
    }
    buffer[0] = x;
    
    
    // fir
    y = 0.25 * buffer[0] + 0.5 * buffer[1] + 0.25 * buffer[2];
    
    return y;
}
