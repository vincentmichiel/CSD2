#include "StereoDelay.h"

StereoDelay::StereoDelay(float lDelayTime, float rDelayTime, int sampleRate) : Effect() {
	m_buffer[0] = new CircBuffer(lDelayTime, sampleRate);
	m_buffer[1] = new CircBuffer(rDelayTime, sampleRate);
}

StereoDelay::~StereoDelay(){
	delete m_buffer[0];
	delete m_buffer[1];
}

void StereoDelay::tick(int channel){
	m_buffer[channel]->tick();
}
	
float StereoDelay::applyEffect(float sample, int channel){
	// STEREO EFFECTS
	m_buffer[channel]->write(sample);
	return m_buffer[channel]->read();
}