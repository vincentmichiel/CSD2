#include <Bela.h>
#include <libraries/Fft/Fft.h>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
#include "FFTEffect.h"


FFTEffect::FFTEffect() {
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
	
	// Set up the thread for the FFT
	gFftTask = Bela_createAuxiliaryTask(FFTEffect::process_fft_background_static, 50, "bela-process-fft", (void*)this);
	rt_printf("FFT Effect created successfully\n");
}

FFTEffect::~FFTEffect(){};


void  FFTEffect::process_fft(std::vector<float> const& inBuffer, unsigned int inPointer, std::vector<float>& outBuffer, unsigned int outPointer){
	static std::vector<float> unwrappedBuffer(gFftSize);	// Container to hold the unwrapped time-domain values
	
	// These containers hold the converted representation from magnitude-phase into magnitude-frequency
	static std::vector<float> analysisMagnitudes(gFftSize / 2 + 1);
	static std::vector<float> analysisFrequencies(gFftSize / 2 + 1);
	static std::vector<float> synthesisMagnitudes(gFftSize / 2 + 1);
	static std::vector<float> synthesisFrequencies(gFftSize / 2 + 1);
	
	// Copy buffer into FFT input
	for(int n = 0; n < gFftSize; n++) {
		// Use modulo arithmetic to calculate the circular buffer index
		int circularBufferIndex = (inPointer + n - gFftSize + gBufferSize) % gBufferSize;
		unwrappedBuffer[n] = inBuffer[circularBufferIndex] * gAnalysisWindowBuffer[n];
	}
	
	// Process the FFT based on the time domain input
	gFft.fft(unwrappedBuffer);
		
	// fft processing in effect class
	processSpectrum();
	
	// Run the inverse FFT
	gFft.ifft();
	
	// Add timeDomainOut into the output buffer
	for(int n = 0; n < gFftSize; n++) {
		int circularBufferIndex = (outPointer + n - gFftSize + gBufferSize) % gBufferSize;
		outBuffer[circularBufferIndex] += gFft.td(n) * gSynthesisWindowBuffer[n];
	}
}

// This function runs in an auxiliary task on Bela, calling process_fft
void FFTEffect::process_fft_background()
{
	process_fft(gInputBuffer, gCachedInputBufferPointer, gOutputBuffer, gOutputBufferWritePointer);

	// Update the output buffer write pointer to start at the next hop
	gOutputBufferWritePointer = (gOutputBufferWritePointer + gHopSize) % gBufferSize;
}

void FFTEffect::process_fft_background_static(void *arg){
		FFTEffect* that = (FFTEffect*)arg;
    	that->process_fft_background();
}

float FFTEffect::process(float in){
	// Store the sample ("in") in a buffer for the FFT
		// Increment the pointer and when full window has been 
		// assembled, call process_fft()
		gInputBuffer[gInputBufferPointer++] = in;
		if(gInputBufferPointer >= gBufferSize) {
			// Wrap the circular buffer
			// Notice: this is not the condition for starting a new FFT
			gInputBufferPointer = 0;
		}
		
		// Get the output sample from the output buffer
		float out = gOutputBuffer[gOutputBufferReadPointer];
		
		// Then clear the output sample in the buffer so it is ready for the next overlap-add
		gOutputBuffer[gOutputBufferReadPointer] = 0;
		
		// Scale the output down by the scale factor, compensating for the overlap
		out *= gScaleFactor;
		
		// Increment the read pointer in the output cicular buffer
		gOutputBufferReadPointer++;
		if(gOutputBufferReadPointer >= gBufferSize)
			gOutputBufferReadPointer = 0;
		
		// Increment the hop counter and start a new FFT if we've reached the hop size
		if(++gHopCounter >= gHopSize) {
			gHopCounter = 0;
			
			gCachedInputBufferPointer = gInputBufferPointer;
			Bela_scheduleAuxiliaryTask(gFftTask);
		}
		
	return out;
}

void FFTEffect::processSpectrum(){};