/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    NewProjectAudioProcessor& audioProcessor;
    
    // ui objects
    juce::Slider lowShelfGain;
    juce::Slider highShelfGain;
    juce::Slider resonatorFrequency;
    juce::Slider resonatorDepth;
    juce::Slider reEsserThreshHold;
    juce::Slider reEsserMix;
    juce::Slider sidechainGain;
    juce::Slider sidechainMix;
    
    // modulation sources
    juce::Slider resonatorFrequencyLFO;
    juce::Slider resonatorFrequencyLFODepth;
    
    void sliderValueChanged(juce::Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
