//
//  DFI.hpp
//  
//
//  Created by Vincent Van den Broeck on 12/09/2024.
//

#ifndef DFI_hpp
#define DFI_hpp

#include <stdio.h>

class DFI {
private:
    unsigned int bufferSize;
    double y;
    double * buffer;
    double * outputBuffer;
    double b0;
    double b1;
    double a1;
public:
    DFI();
    ~DFI();
    double process(double x);
    void clear();
};

#endif /* DFI_hpp */
