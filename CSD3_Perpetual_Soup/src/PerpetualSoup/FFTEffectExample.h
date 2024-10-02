#include "FFTEffect.h"

class FFTEffectExample : public FFTEffect {
	public:
	using FFTEffect::FFTEffect;
	~FFTEffectExample();
	
	private:
	void processSpectrum() override;
};