/*
 ==============================================================================
 
 FFT.cpp
 Created: 11 May 2024 1:16:32pm
 Author:  Vincent Van den Broeck
 
 ==============================================================================
 */

#include "FFT.h"

FFT::FFT() : fft(fftOrder), window(fftSize + 1, juce::dsp::WindowingFunction<float>::WindowingMethod::hann, false) {
    count = 0;
    pos = 0;
}

FFT::~FFT(){};

int FFT::getLatencyInSamples() const {
    return pow(2, fftOrder);
}

void FFT::reset(){
    count = 0;
    pos = 0;
    std::fill(inputFifo.begin(), inputFifo.end(), 0.0f);
    std::fill(outputFifo.begin(), outputFifo.end(), 0.0f);
}

float FFT::processSample(float sample, bool bypassed) {
    inputFifo[pos] = sample;
    
    // store output sample
    float outputSample = outputFifo[pos];
    outputFifo[pos] = 0.0f;
    
    pos += 1;
    // constrain pos
    if (pos == fftSize) {
        pos = 0;
    }
    
    // constrain pos and apply fft when buffer is filled
    count += 1;
    if (count == hopSize) {
        count = 0;
        processFrame(bypassed);
    }
    
    return outputSample;
}

void FFT::processFrame(bool bypassed) {
    const float* inputPtr = inputFifo.data();
    float* fftPtr = fftData.data();
    
    std::memcpy(fftPtr, inputPtr + pos, (fftSize - pos) * sizeof(float));
    if (pos > 0) {
        std::memcpy(fftPtr + fftSize - pos, inputPtr, pos * sizeof(float));
    }
    
    // apply windowing
    window.multiplyWithWindowingTable(fftPtr, fftSize);
    
    // apply fft
    if (!bypassed) {
        fft.performRealOnlyForwardTransform(fftPtr, true);  // FFT
        processSpectrum(fftPtr, numBins);
        fft.performRealOnlyInverseTransform(fftPtr);        // IFFT
    }
    
    // apply output windowing
    window.multiplyWithWindowingTable(fftPtr, fftSize);
    
    for (int i = 0; i < fftSize; ++i) {
        fftPtr[i] *= windowCorrection;
    }
    
    // write to output buffer
    for (int i = 0; i < pos; ++i) {
        outputFifo[i] += fftData[i + fftSize - pos];
    }
    for (int i = 0; i < fftSize - pos; ++i) {
        outputFifo[i + pos] += fftData[i];
    }
}

void FFT::processSpectrum(float* data, int numBins){};
