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
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    threshHold.setSliderStyle (juce::Slider::LinearBarVertical);
    threshHold.setRange (0.0, 1.0, 0.01);
    threshHold.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    threshHold.setPopupDisplayEnabled (true, false, this);
    threshHold.setTextValueSuffix (" Threshold");
    threshHold.setValue(audioProcessor.threshHold);
    threshHold.addListener(this);
    addAndMakeVisible (&threshHold);
    
    bandWidth.setSliderStyle (juce::Slider::LinearBarVertical);
    bandWidth.setRange (0.0, 1.0, 0.01);
    bandWidth.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    bandWidth.setPopupDisplayEnabled (true, false, this);
    bandWidth.setTextValueSuffix (" Bandwidth");
    bandWidth.setValue(audioProcessor.bandWidth);
    bandWidth.addListener(this);
    addAndMakeVisible (&bandWidth);
    
    centerFrequency.setSliderStyle (juce::Slider::LinearBarVertical);
    centerFrequency.setRange (20, 20000, 1.0f);
    centerFrequency.setSkewFactor(0.2);
    centerFrequency.setTextValueSuffix("Hz");
    centerFrequency.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    centerFrequency.setPopupDisplayEnabled (true, false, this);
    centerFrequency.setTextValueSuffix (" Center Frequency");
    centerFrequency.setValue(audioProcessor.centerFrequency);
    centerFrequency.addListener(this);
    addAndMakeVisible (&centerFrequency);
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
    g.drawFittedText ("Version 1.10 - ReEsser", getLocalBounds(), juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    threshHold.setBounds (30, 30, 20, getHeight() - 60);
    bandWidth.setBounds (50, 30, 20, getHeight() - 60);
    centerFrequency.setBounds(70, 30, 20, getHeight() - 60);
}

void NewProjectAudioProcessorEditor::sliderValueChanged(juce::Slider* slider){
    audioProcessor.threshHold = threshHold.getValue();
    audioProcessor.bandWidth = bandWidth.getValue();
    audioProcessor.centerFrequency = centerFrequency.getValue();
}
