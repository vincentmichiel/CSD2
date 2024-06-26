/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Oscillator.hpp";
#include "ShelfFilter.h"
#include "Resonator.h"
#include "ReEsser.h"
#include "Chordifyer.h"

//==============================================================================
/**
*/
class NewProjectAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    NewProjectAudioProcessor();
    ~NewProjectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // ui variables
    float lowShelfGain = 0;
    float highShelfGain = 0;
    float resonatorFrequency = 440;
    float resonatorDepth = 0;
    float reEsserThreshHold = 1.0f;
    float reEsserMix = 0;
    float sidechainGain = 0;
    float sidechainMix = 0;
    
    // modulation values
    float LFO1freq = 2;
    float LFO1phase = 0;
    float LFO1depth = 0;
    float LFO2freq = 2;
    float LFO2phase = 0;
    float LFO2depth = 0;
    float LFO3freq = 2;
    float LFO3phase = 0;
    float LFO3depth = 0;
    float LFO4freq = 2;
    float LFO4phase = 0;
    float LFO4depth = 0;
    
    float LFO5freq = 2;
    float LFO5phase = 0;
    float LFO5depth = 0;
    float LFO6freq = 2;
    float LFO6phase = 0;
    float LFO6depth = 0;
    float LFO7freq = 2;
    float LFO7phase = 0;
    float LFO7depth = 0;
    float LFO8freq = 2;
    float LFO8phase = 0;
    float LFO8depth = 0;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessor)
    
    // dsp modules
    ShelfFilter lowShelfFilter[2];
    ShelfFilter highShelfFilter[2];
    Resonator resonator[2];
    ReEsser reEsser[2];
    Chordifyer chordifyer[2];
    
    // mod sources
    Sine LFO1[2];
    Sine LFO2[2];
    Sine LFO3[2];
    Sine LFO4[2];
    
    Sine LFO5[2];
    Sine LFO6[2];
    Sine LFO7[2];
    Sine LFO8[2];
    
    // tick
    void tick(int channel);
};
