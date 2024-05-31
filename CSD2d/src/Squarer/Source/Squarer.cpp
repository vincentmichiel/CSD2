/*
  ==============================================================================

    Squarer.cpp
    Created: 21 May 2024 8:58:02am
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#include "Squarer.h"
#include "Oscillator.hpp"
#include "Interpolate.h"

Squarer::~Squarer(){};

void Squarer::prepare(float frequency, float depth, double samplerate){
    lfo = new Block(frequency, depth, samplerate);
}

void Squarer::setDepth(float depth){
    this->depth = depth;
}

void Squarer::processSpectrum(float* data)
{
    auto* cdata = reinterpret_cast<std::complex<float>*>(data);
    float normalisedLevelValues[numBins];
    
    for(int i = 0; i < numBins; i++){
        normalisedLevelValues[i] = std::abs(spectrumAnalyser.sidechainFFT[i]);
    }
    
    juce::Range<float> levelsMinMax = juce::FloatVectorOperations::findMinAndMax(normalisedLevelValues, numBins);
    
    
    // spectral processing
    
    for (int i = 0; i < numBins; ++i) {
        float magnitude = std::abs(cdata[i]);
        float phase = std::arg(cdata[i]);
        
        normalisedLevelValues[i] = Interpolate::mapInRange(normalisedLevelValues[i], (float) levelsMinMax.getStart(), (float) levelsMinMax.getEnd(), 0, 1);
        
        magnitude *= (1 - depth);
        magnitude += normalisedLevelValues[i] * depth;
        
        
        // backwards conversion
        cdata[i] = std::polar(magnitude, phase);
    }
}
