#include "CircBuffer.h"
#include <iostream>
#include <cstring>
#include <vector>


CircBuffer::CircBuffer(float delayTime, int sampleRate) : m_size(delayTime * sampleRate) , m_sampleRate(sampleRate) {
    m_buffer.resize(m_size);
    m_writeH = m_size -1;
    m_readH = 0;
}

CircBuffer::~CircBuffer()
{
    m_buffer.clear();
}

void CircBuffer::resetSize(float delayTime)
{
    m_size = delayTime * m_sampleRate;
    m_buffer.clear();
    m_buffer.resize(m_size);
    m_writeH = m_size -1;
    m_readH = 0;
}
