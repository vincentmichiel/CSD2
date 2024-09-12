//
//  DFII.hpp
//  
//
//  Created by Vincent Van den Broeck on 12/09/2024.
//

#ifndef DFII_hpp
#define DFII_hpp

#include <stdio.h>

class DFII {
private:
    unsigned int bufferSize;
    double y;
    double w;
    double * buffer;
    double b0;
public:
    DFII();
    ~DFII();
    double process(double x);
    void clear();
};

#endif /* DFII_hpp */
