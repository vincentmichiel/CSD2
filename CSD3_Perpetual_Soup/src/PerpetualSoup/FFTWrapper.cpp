#include <Bela.h>
#include <libraries/Fft/Fft.h>
#include <libraries/Scope/Scope.h>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
#include "FFTWrapper.h"

FFTWrapper::FFTWrapper(){
	// Set up the FFT and its buffers
	gFft.setup(gFftSize);
	gInputBuffer.resize(gBufferSize);
	gOutputBuffer.resize(gBufferSize);
	
	// Calculate the windows
	gAnalysisWindowBuffer.resize(gFftSize);
	gSynthesisWindowBuffer.resize(gFftSize);
	for(int n = 0; n < gFftSize; n++) {
		// Hann window, split across analysis and synthesis windows
		gAnalysisWindowBuffer[n] = 0.5f * (1.0f - cosf(2.0 * M_PI * n / (float)(gFftSize - 1)));
		gSynthesisWindowBuffer[n] = gAnalysisWindowBuffer[n];
	}
}

void FFTWrapper::process_fft(std::vector<float> const& inBuffer, unsigned int inPointer, std::vector<float>& outBuffer, unsigned int outPointer)
{
	static std::vector<float> unwrappedBuffer(gFftSize);	// Container to hold the unwrapped time-domain values
	
	
	// Copy buffer into FFT input
	for(int n = 0; n < gFftSize; n++) {
		// Use modulo arithmetic to calculate the circular buffer index
		int circularBufferIndex = (inPointer + n - gFftSize + gBufferSize) % gBufferSize;
		unwrappedBuffer[n] = inBuffer[circularBufferIndex] * gAnalysisWindowBuffer[n];
	}
	
	// Process the FFT based on the time domain input
	gFft.fft(unwrappedBuffer);
		
		
	for(int n = 0; n <= gFftSize/2; n++) {
		// Turn real and imaginary components into amplitude and phase
		float amplitude = gFft.fda(n);
		float phase = atan2f(gFft.fdi(n), gFft.fdr(n));
		
		// FFT processing
		/////////////////
		if(n < 20){
			amplitude = 0;
		}
		
		// TODO: Now convert magnitude and phase back to real and imaginary components
		gFft.fdr(n) = amplitude * cosf_neon(phase);
		gFft.fdi(n) = amplitude * sinf_neon(phase);
		
		// Also store the complex conjugate in the upper half of the spectrum
		if(n > 0 && n < gFftSize / 2) {
			gFft.fdr(gFftSize - n) = gFft.fdr(n);
			gFft.fdi(gFftSize - n) = -gFft.fdi(n);
		}
	}	
	
	gFft.ifft();
	// Add timeDomainOut into the output buffer
	for(int n = 0; n < gFftSize; n++) {
		int circularBufferIndex = (outPointer + n - gFftSize + gBufferSize) % gBufferSize;
		outBuffer[circularBufferIndex] += gFft.td(n) * gSynthesisWindowBuffer[n];
	}
}

float FFTWrapper::process(float sample){
	gInputBuffer[gInputBufferPointer] = sample;
    
    // store output sample
    float outputSample = gOutputBuffer[gOutputBufferReadPointer];
    gOutputBuffer[gOutputBufferReadPointer] = 0.0f;
    
    outputSample *= gScaleFactor;
    
    gInputBufferPointer += 1;
    gOutputBufferReadPointer += 1;
    // constrain buffer pointers
    if(gInputBufferPointer >= gBufferSize) {
		gInputBufferPointer = 0;
	}
	if(gOutputBufferReadPointer >= gBufferSize) {
		gOutputBufferReadPointer = 0;
	}
    
    // Increment the hop counter and start a new FFT if we've reached the hop size
	if(++gHopCounter >= gHopSize) {
		gHopCounter = 0;
			
		gCachedInputBufferPointer = gInputBufferPointer;
		
		// process buffer
		process_fft(gInputBuffer, gCachedInputBufferPointer, gOutputBuffer, gOutputBufferWritePointer);

		// Update the output buffer write pointer to start at the next hop
		gOutputBufferWritePointer = (gOutputBufferWritePointer + gHopSize) % gBufferSize;
	}
    
    return outputSample;
}
