//
//  AllpassBuffer.hpp
//  Autoverb
//
//  https://github.com/TimSchippers/CSD/blob/main/CSD2c/stereoEffect/circularBuffer.h
//

#ifndef AllpassBuffer_hpp
#define AllpassBuffer_hpp

#include "interpolation.cpp"
#include <iostream>
#include <ostream>

class AllpassBuffer {
public:
    AllpassBuffer();
    AllpassBuffer(int size);
    ~AllpassBuffer();
    
    inline void write(float sample) {
        buffer[indexWriteHead] = sample;
        indexWriteHead++;
        wrapHead(indexWriteHead);
    };
    
    inline float read() {
        float signal = buffer[indexReadHead];
        indexReadHead++;
        wrapHead(indexReadHead);
        return signal;
    };
    
    inline float readLinear() {
        indexReadHead = (int)indexReadHeadFloat;
        float indexRemainder = indexReadHeadFloat - indexReadHead;
        int nextIndex = indexReadHead + 1;
        wrapHead(nextIndex);
        float signal = Interpolation::linearInterpolation(
                                                          indexRemainder, buffer[indexReadHead], buffer[nextIndex]);
        indexReadHeadFloat++;
        wrapHeadFloat(indexReadHeadFloat);
        return signal;
    }
    
    // setters
    void setDistanceReadHead(float samples);
    void setSize(int size);
    
private:
    inline void wrapHead(int &head) {
        if (head >= size)
            head -= size;
        else if (head < 0)
            head += size;
    }
    inline void wrapHeadFloat(float &head) {
        if (head >= size)
            head -= size;
        else if (head < 0)
            head += size;
    }
    
    int indexWriteHead;
    int indexReadHead;
    float indexReadHeadFloat;
    
    int size;
    float distance;
    
    float *buffer;
};

#endif /* AllpassBuffer_hpp */
