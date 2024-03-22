//
//  CircBuffer.hpp
//  effects1
//
//  Created by Vincent Van den Broeck on 08/02/2024.
//

#ifndef CircBuffer_hpp
#define CircBuffer_hpp

typedef unsigned int uint;

class CircBuffer {
public:
    /*
     * size: the number of samples in the buffer
     */
    
    CircBuffer();
    CircBuffer(uint size, uint distanceRW);
    CircBuffer(uint size, uint * distances, uint tapAmount);
    ~CircBuffer();
    
    // resets the size of the buffer
    void resetSize(uint size);
    
    // setter and getter for the distance between read and write head
    void setDistanceRW(uint distanceRW);
    void setDistances(uint * distances);
    void setTapAmount(uint tapAmount);
    uint getDistanceRW();
    // write and read values at write / read head
    inline void write(float val) { m_buffer[m_writeH] = val; }
    inline float read() { return m_buffer[m_readH]; }
    
    inline float readTaps() {
        float output = 0;
        for(int i = 0; i < tapAmount; i++){
            output += m_buffer[readHeads[i]];
        }
        return output / tapAmount;
    }
    
    // method to set a step in time --> move to next sample
    inline void tick() {
        incrWriteH();
        incrReadH();
        
        if(tapAmount > 0){
            for(int i = 0; i < tapAmount; i++){
                readHeads[i]++;
                wrapH(readHeads[i]);
            }
        }
    }
    
    // debug methods
    void logRWPos();
    void logDistanceRW();
    void logSize();
    void logAllSettings();
    void logAllValues();
    
private:
    // increase write and read heads ands wrap if necessary
    inline void incrWriteH() {
        m_writeH++;
        wrapH(m_writeH);
    }
    
    inline void incrReadH() {
        m_readH++;
        wrapH(m_readH);
    }
    
    // wrap a head if necessary
    inline void wrapH(int& head) {
        if (head >= m_size) {
            head -= m_size;
        } else if (head < 0){
            head += m_size;
        }
    }
    
    // allocate and release methods, used to alter the buffer size
    void allocateBuffer();
    void releaseBuffer();
    
    // pointer to the buffer
    float* m_buffer;\
    // buffer size
    uint m_size;
    // read and write heads, delay size
    int m_readH;
    int m_writeH;
    uint m_distanceRW;
    uint tapAmount;
    uint * distances;
    int * readHeads;
};

#endif /* CircBuffer_hpp */
