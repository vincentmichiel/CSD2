//
//  DFI.cpp
//  
//
//  Created by Vincent Van den Broeck on 12/09/2024.
//

#include "DFI.hpp"
#include <iostream>	

DFI::DFI(){
    bufferSize = 8;
    b0 = 0.1678;
    b1 = -1;
    a1 = 0.1678;
    buffer = (double*)malloc(bufferSize * sizeof(double));
    outputBuffer = (double*)malloc(bufferSize * sizeof(double));
    memset(buffer, 0.0, bufferSize * sizeof(double));
    memset(outputBuffer, 0.0, bufferSize * sizeof(double));
}

DFI::~DFI(){
    free(buffer);
    free(outputBuffer);
}

void DFI::clear(){
    memset(buffer, 0.0, bufferSize * sizeof(double));
    memset(outputBuffer, 0.0, bufferSize * sizeof(double));
}

double DFI::process(double x){
    //DFI
    y = b0 * x + b1 * buffer[bufferSize - 1] + a1 * outputBuffer[bufferSize - 1];
    
    // shift output values
    for(int i = bufferSize - 1; i > 0; i--){
        buffer[i] = buffer[i - 1];
        outputBuffer[i] = outputBuffer[i - 1];
    }
    
    // store input
    buffer[0] = x;
    // store output
    outputBuffer[0] = y;
    
    return y;
}

