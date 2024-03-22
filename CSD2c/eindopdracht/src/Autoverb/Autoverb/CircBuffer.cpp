//
//  CircBuffer.cpp
//  effects1
//
//  Created by Vincent Van den Broeck on 08/02/2024.
//

#include "CircBuffer.hpp"
#include <iostream>
#include <cstring>

CircBuffer::CircBuffer() : CircBuffer(0, 256) {
    tapAmount = 0;
}

CircBuffer::CircBuffer(uint size, uint distanceRW) : m_size(size),
m_readH(0), m_writeH(0)
{
    allocateBuffer();
    setDistanceRW(distanceRW);
    
    // fill buffer
    memset(m_buffer, 0, m_size * sizeof(float));
}

CircBuffer::CircBuffer(uint size, uint * distances, uint tapAmount) : m_size(size),
m_readH(0), m_writeH(0), tapAmount(tapAmount)
{
    allocateBuffer();
    
    // fill buffer
    memset(m_buffer, 0, m_size * sizeof(float));
}

CircBuffer::~CircBuffer()
{
    releaseBuffer();
}

void CircBuffer::resetSize(uint size)
{
    m_size = size;
    releaseBuffer();
    allocateBuffer();
}

void CircBuffer::setTapAmount(uint tapAmount){
    this->tapAmount = tapAmount;
}

void CircBuffer::allocateBuffer()
{
    // allocate buffer and set all samples to 0
    m_buffer = (float*)malloc(m_size * sizeof(float));
    memset(m_buffer, 0, m_size * sizeof(float));
}

void CircBuffer::releaseBuffer()
{
    // free data allocated with memset
    free(m_buffer);
}

void CircBuffer::setDistanceRW(uint distanceRW)
{
    // store new distance between R & W heads and update rhead position
    m_distanceRW = distanceRW;
    m_readH = m_writeH - m_distanceRW + m_size;
    wrapH(m_readH);
}

void CircBuffer::setDistances(uint * distances)
{
    // store new distance between R & W heads and update rhead position
    this->distances = distances;
    readHeads = new int[tapAmount];
    
    for(int i = 0; i < tapAmount; i++){
        readHeads[i] = m_writeH - distances[i] + m_size;
        std::cout << i << std::endl;
        wrapH(readHeads[i]);
    }
}

uint CircBuffer::getDistanceRW() {
    return m_distanceRW;
}

void CircBuffer::logRWPos()
{
    std::cout << "\n______________________ CircBuffer ______________________________\n";
    std::cout << "Read head position: " << m_readH << "\n";
    std::cout << "Write head position: " << m_writeH << "\n";
    std::cout << "_________________________________________________________________\n";
}

void CircBuffer::logDistanceRW()
{
    std::cout << "\n______________________ CircBuffer ______________________________\n";
    std::cout << "Distance between read and write head: " << m_distanceRW << "\n";
    std::cout << "_________________________________________________________________\n";
}


void CircBuffer::logSize()
{
    std::cout << "\n______________________ CircBuffer ______________________________\n";
    std::cout << "Buffer size: " << m_size << "\n";
    std::cout << "_________________________________________________________________\n";
}

void CircBuffer::logAllSettings()
{
    std::cout << "\n______________________ CircBuffer ______________________________\n";
    std::cout << "Read head position: " << m_readH << "\n";
    std::cout << "Write head position: " << m_writeH << "\n";
    std::cout << "Distance between read and write head: " << m_distanceRW << "\n";
    std::cout << "Buffer size: " << m_size << "\n";
    std::cout << "_________________________________________________________________\n";
}


void CircBuffer::logAllValues()
{
    std::cout << "\n______________________ CircBuffer ______________________________\n";
    std::cout << "CircBuffer - buffer contains: \n";
    for (int i = 0; i < m_size - 1; i++)
    {
        std::cout << m_buffer[i] << ", ";
    }
    std::cout << m_buffer[m_size - 1] << "\n";
    std::cout << "_________________________________________________________________\n";
}
