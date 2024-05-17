/*
 ==============================================================================
 
 FFT.h
 Created: 11 May 2024 1:16:32pm
 Author:  Vincent Van den Broeck
 
 FFT Wrapper based on https://audiodev.blog/fft-processing/
 
 ==============================================================================
 */

#pragma once
#include <JuceHeader.h>

class FFT {
public:
    FFT();
    virtual ~FFT();
    int getLatencyInSamples() const;
    void reset();
    float processSample(float sample, bool bypassed);
    void processBlock(float* data, int numSamples, bool bypassed);
    void setSampleRate(double sampleRate);
    double getSampleRate();
    
    static constexpr int fftOrder = 10;
    static constexpr int fftSize = 1 << fftOrder;      // left shift operator << 1024 samples
    
protected:
    double sampleRate;
    std::array<float, fftSize> inputFifo;
    std::array<float, fftSize> outputFifo;
    std::array<float, fftSize * 2> fftData;
    
    static constexpr int numBins = fftSize / 2 + 1;    // 513 bins (up to niquist)
    static constexpr int overlap = 4;                  // 75% overlap
    static constexpr int hopSize = fftSize / overlap;  // 256 samples
    
    virtual void processSpectrum(float* data);
    float calcBinFromFrequency(float frequency);
    float calcFrequencyFromBin(int bin);

private:
    void processFrame(bool bypassed);
    
    juce::dsp::FFT fft;
    juce::dsp::WindowingFunction<float> window;
    static constexpr float windowCorrection = 2.0f / 3.0f;
    
    int count;
    int pos;
};
