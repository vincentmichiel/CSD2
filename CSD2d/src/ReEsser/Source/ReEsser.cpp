/*
  ==============================================================================

    ReEsser.cpp
    Created: 17 May 2024 11:19:37am
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#include "ReEsser.h"
#include "Interpolate.h"

ReEsser::~ReEsser(){};

void ReEsser::setThreshHold(float threshHold){
    this->threshHold = threshHold;
}

void ReEsser::setCenterFrequency(float frequency){
    target = frequency;
}

void ReEsser::setBandWidth(float bandWidth){
    this->bandWidth = bandWidth;
}

void ReEsser::processSpectrum(float* data)
{
    auto* cdata = reinterpret_cast<std::complex<float>*>(data);
    float normalisedLevelValues[numBins];
    
    for(int i = 0; i < numBins; i++){
        normalisedLevelValues[i] = std::abs(cdata[i]);
    }
    
    juce::Range<float> levelsMinMax = juce::FloatVectorOperations::findMinAndMax(normalisedLevelValues, numBins);
   
    
    // spectral processing
    // scale bandwidth
    bandWidth = Interpolate::mapInRange(bandWidth, 0, 1, 8, 1);
    
    for (int i = 0; i < numBins; ++i) {
        float magnitude = std::abs(cdata[i]);
        float phase = std::arg(cdata[i]);
        float freq = calcFrequencyFromBin(i);
        
        normalisedLevelValues[i] = Interpolate::mapInRange(normalisedLevelValues[i], (float) levelsMinMax.getStart(), (float) levelsMinMax.getEnd(), 0, 1);
        float distance = std::max(target, freq) - std::min(target, freq);
        
        
        
        // amplify frequencies when close to target and above threshold
        if(distance < target / bandWidth && normalisedLevelValues[i] > threshHold){
            float amp = Interpolate::mapInRange(normalisedLevelValues[i], 0, 1, 10, 1);
            magnitude *= 5 * amp;
        }
        
        
        // backwards conversion
        cdata[i] = std::polar(magnitude, phase);
    }
}
