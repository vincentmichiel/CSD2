//
//  AllpassFilter.hpp
//  Autoverb
//  credit to
//  https://github.com/TimSchippers/CSD/blob/main/CSD2c/stereoEffect/allPassFilter.h
//

#ifndef AllpassFilter_hpp
#define AllpassFilter_hpp

#include <stdio.h>
#include "AllpassBuffer.hpp"
// an all pass filter based on the formula found in
// the book "Designing audio effect plugins by Will C. Pirkle
class AllPassFilter {
public:
    AllPassFilter(float milliseconds, float feedback);
    ~AllPassFilter();
    
    float process(float input);
    void setFeedback(float feedback);
    void setDelayTime(float milliseconds);
    void clear(float milliseconds);
    
private:
    int samplerate;
    AllpassBuffer* buffer;
    float numSamplesDelay;
    float feedbackAmount;
};

#endif /* AllpassFilter_hpp */
