//
//  DFII.cpp
//  
//
//  Created by Vincent Van den Broeck on 12/09/2024.
//

#include "DFII.hpp"
#include <iostream>

DFII::DFII(){
    bufferSize = 8;
    b0 = 0.1678;
    buffer = (double*)malloc(bufferSize * sizeof(double));
    memset(buffer, 0.0, bufferSize * sizeof(double));
}

DFII::~DFII(){
    free(buffer);
}

void DFII::clear(){
    memset(buffer, 0.0, bufferSize * sizeof(double));
}

double DFII::process(double x){
    //DFII
    w = b0 * buffer[bufferSize - 1] + x;
    y = b0 * w - buffer[bufferSize -1];
    
    // shift buffer
    for(int i = bufferSize - 1; i > 0; i--){
        buffer[i] = buffer[i - 1];
    }
    
    // store input
    buffer[0] = w;
    
    return y;
}


