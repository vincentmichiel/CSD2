/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (800, 500);
    
    lowShelfGain.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    lowShelfGain.setRange (-12.0f, 12.0f, 0.0f);
    lowShelfGain.setNumDecimalPlacesToDisplay(1);
    lowShelfGain.setTextValueSuffix("dB");
    lowShelfGain.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    lowShelfGain.setPopupDisplayEnabled (true, false, this);
    lowShelfGain.setTextValueSuffix (" Low Gain");
    lowShelfGain.setValue(audioProcessor.lowShelfGain);
    lowShelfGain.addListener(this);
    addAndMakeVisible (&lowShelfGain);
    
    highShelfGain.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    highShelfGain.setRange (-12.0f, 12.0f, 0.0f);
    highShelfGain.setNumDecimalPlacesToDisplay(1);
    highShelfGain.setTextValueSuffix("dB");
    highShelfGain.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    highShelfGain.setPopupDisplayEnabled (true, false, this);
    highShelfGain.setTextValueSuffix (" High Gain");
    highShelfGain.setValue(audioProcessor.highShelfGain);
    highShelfGain.addListener(this);
    addAndMakeVisible (&highShelfGain);
    
    
    
    
    
    resonatorFrequency.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    resonatorFrequency.setRange (20, 20000, 1.0f);
    resonatorFrequency.setSkewFactor(0.2);
    resonatorFrequency.setTextValueSuffix("Hz");
    resonatorFrequency.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    resonatorFrequency.setPopupDisplayEnabled (true, false, this);
    resonatorFrequency.setTextValueSuffix (" Resonator Frequency");
    resonatorFrequency.setValue(audioProcessor.resonatorFrequency);
    resonatorFrequency.addListener(this);
    addAndMakeVisible (&resonatorFrequency);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    lowShelfGain.setBounds(30, 30, 80, 80);
    highShelfGain.setBounds(120, 30, 80, 80);
    resonatorFrequency.setBounds(30, 80, 80, 80);
}

void NewProjectAudioProcessorEditor::sliderValueChanged(juce::Slider* slider){
    audioProcessor.resonatorFrequency = resonatorFrequency.getValue();
}
