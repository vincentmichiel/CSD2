//
//  RMSController.hpp
//  Autoverb
//
//  Created by Vincent Van den Broeck on 24/03/2024.
//

#ifndef RMSController_hpp
#define RMSController_hpp

#include <stdio.h>
#include "CircBuffer.hpp"

class RMSController {
private:
    CircBuffer * buffer;
    CircBuffer * controlValueHistory;
    uint bufferSize;
    float controlValue;
    float rms;
    void calcRMS();
    
public:
    RMSController(uint bufferSize = 512);
    ~RMSController();
    void write(float sample);
    float getControlValue();
    void tick();
};

#endif /* RMSController_hpp */
