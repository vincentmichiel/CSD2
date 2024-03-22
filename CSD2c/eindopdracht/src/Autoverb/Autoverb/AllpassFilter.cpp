//
//  AllpassFilter.cpp
//  Autoverb
//  credit to
//  https://github.com/TimSchippers/CSD/blob/main/CSD2c/stereoEffect/allPassFilter.cpp
//

#include "AllpassFilter.hpp"
#include <ostream>

AllPassFilter::AllPassFilter(float milliseconds, float feedback)
: feedbackAmount(feedback) {
    samplerate = 44100;
    buffer = new AllpassBuffer;
    setDelayTime(milliseconds);
};
AllPassFilter::~AllPassFilter(){
    delete buffer;
};

float AllPassFilter::process(float input) {
    float output = 0;
    float sample = buffer->readLinear();
    output = -feedbackAmount * input + sample + feedbackAmount * sample;
    buffer->write(input + sample * feedbackAmount);
    return output;
};
void AllPassFilter::setFeedback(float feedback) { feedbackAmount = feedback; };

void AllPassFilter::setDelayTime(float milliseconds) {
    numSamplesDelay = samplerate * (milliseconds / 1000);
    
    buffer->setSize(numSamplesDelay + 1);
    buffer->setDistanceReadHead(numSamplesDelay);
};

void AllPassFilter::clear(float milliseconds){
    delete buffer;
    buffer = new AllpassBuffer;
    setDelayTime(milliseconds);
}
