/*
  ==============================================================================

    ShelfFilter.cpp
    Created: 1 Jun 2024 5:07:16pm
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#include "ShelfFilter.h"
#include "Interpolate.h"

ShelfFilter::~ShelfFilter(){};

void ShelfFilter::prepare(){
    middleBin = (int) round(calcBinFromFrequency(800));
    setDrive(0);
}

void ShelfFilter::setAffectsLowEnd(bool affectsLowEnd){
    this->affectsLowEnd = affectsLowEnd;
}

void ShelfFilter::setDrive(float driveDb){
    if(driveDb > 0){
        drive = 1 * (1 + driveDb / 3.0f);
    } else if (driveDb < 0){
        drive = 1 / (1 + abs(driveDb) / 3.0f);
    } else {
        drive = 1;
    }
}

void ShelfFilter::processSpectrum(float* data)
{
    auto* cdata = reinterpret_cast<std::complex<float>*>(data);

    if(affectsLowEnd){
        for(int i = 0; i < middleBin; i++){
            float magnitude = std::abs(cdata[i]);
            float phase = std::arg(cdata[i]);
            
            magnitude *= Interpolate::mapInRange(i, 0, middleBin, drive, 1);
            
            // backwards conversion
            cdata[i] = std::polar(magnitude, phase);
        }
    } else {
        for(int i = middleBin; i < numBins; i++){
            float magnitude = std::abs(cdata[i]);
            float phase = std::arg(cdata[i]);
            
            magnitude *= Interpolate::mapInRange(i, middleBin, numBins, 1, drive);
            
            // backwards conversion
            cdata[i] = std::polar(magnitude, phase);
        }
    }
}
