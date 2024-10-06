#include "FFTEffectExample.h"

FFTEffectExample::~FFTEffectExample(){};

void FFTEffectExample::processSpectrum(){
	// Analyse the lower half of the spectrum. The upper half is just
	// the complex conjugate and does not contain any unique information
	for(int n = 0; n <= gFftSize/2; n++) {
		// Turn real and imaginary components into amplitude and phase
		float amplitude = gFft.fda(n);
		float phase = atan2f(gFft.fdi(n), gFft.fdr(n));
		
			// lowpass example
			if(n < 10){
				amplitude = 0;
			}
			
		
		// convert magnitude and phase back to real and imaginary components
		gFft.fdr(n) = amplitude * cosf_neon(phase);
		gFft.fdi(n) = amplitude * sinf_neon(phase);
	}
}