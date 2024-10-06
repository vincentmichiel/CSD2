#include "CircBuffer.h"
#include "Effect.h"

class StereoDelay : public Effect {
	public:
	StereoDelay(float lDelayTime, float rDelayTime, int sampleRate);
	~StereoDelay();
	void tick(int channel);
	
	private:
	CircBuffer * m_buffer[2];
	float applyEffect(float sample, int channel) override;
};