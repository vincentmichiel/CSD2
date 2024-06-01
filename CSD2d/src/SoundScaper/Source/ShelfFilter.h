/*
  ==============================================================================

    ShelfFilter.h
    Created: 1 Jun 2024 5:07:16pm
    Author:  Vincent Van den Broeck

  ==============================================================================
*/

#pragma once

#include "FFT.h"

class ShelfFilter : public FFT {
public:
    using FFT::FFT;
    void prepare();
    ~ShelfFilter();
    void setAffectsLowEnd(bool affectsLowEnd);
    void setDrive(float driveDb);
    
private:
    int middleBin;
    bool affectsLowEnd = false;
    void processSpectrum(float* data) override;
    float gain;
    float drive;
};
