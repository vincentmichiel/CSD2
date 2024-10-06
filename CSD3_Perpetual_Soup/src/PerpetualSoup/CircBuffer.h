#include <Bela.h>
#include <vector>

class CircBuffer {
	public:
	CircBuffer(float delayTime, int sampleRate);
	~CircBuffer();
	
	inline void write(float val) { m_buffer[m_writeH] = val; }
    inline float read() { return m_buffer[m_readH]; }
    
	// method to set a step in time --> move to next sample
    inline void tick() {
        incrWriteH();
        incrReadH();
    }
    
    void resetSize(float delayTime);
	
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
    
    // pointer to the buffer
    std::vector<float> m_buffer;
    // buffer size
    unsigned int m_size;
    // read and write heads, delay size
    int m_readH;
    int m_writeH;
    
    int m_sampleRate;
};