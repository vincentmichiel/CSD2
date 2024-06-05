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
    setSize (520, 300);
    
    lowShelfGain.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    lowShelfGain.setRange (-12.0f, 12.0f, 0.1f);
    lowShelfGain.setNumDecimalPlacesToDisplay(1);
    lowShelfGain.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    lowShelfGain.setPopupDisplayEnabled (true, false, this);
    lowShelfGain.setTextValueSuffix (" Low Gain");
    lowShelfGain.setValue(audioProcessor.lowShelfGain);
    lowShelfGain.addListener(this);
    addAndMakeVisible (&lowShelfGain);
    
    highShelfGain.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    highShelfGain.setRange (-12.0f, 12.0f, 0.1f);
    highShelfGain.setNumDecimalPlacesToDisplay(1);
    highShelfGain.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    highShelfGain.setPopupDisplayEnabled (true, false, this);
    highShelfGain.setTextValueSuffix (" High Gain");
    highShelfGain.setValue(audioProcessor.highShelfGain);
    highShelfGain.addListener(this);
    addAndMakeVisible (&highShelfGain);
    
    resonatorFrequency.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    resonatorFrequency.setRange (20, 20000, 1.0f);
    resonatorFrequency.setSkewFactor(0.2);
    resonatorFrequency.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    resonatorFrequency.setPopupDisplayEnabled (true, false, this);
    resonatorFrequency.setTextValueSuffix (" Frequency");
    resonatorFrequency.setValue(audioProcessor.resonatorFrequency);
    resonatorFrequency.addListener(this);
    addAndMakeVisible (&resonatorFrequency);
    
    resonatorDepth.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    resonatorDepth.setRange (0, 1, 0.01f);
    resonatorDepth.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    resonatorDepth.setPopupDisplayEnabled (true, false, this);
    resonatorDepth.setTextValueSuffix (" Depth");
    resonatorDepth.setValue(audioProcessor.resonatorDepth);
    resonatorDepth.addListener(this);
    addAndMakeVisible (&resonatorDepth);
    
    reEsserThreshHold.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    reEsserThreshHold.setRange (0, 1, 0.01f);
    reEsserThreshHold.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    reEsserThreshHold.setPopupDisplayEnabled (true, false, this);
    reEsserThreshHold.setTextValueSuffix (" Threshold");
    reEsserThreshHold.setValue(audioProcessor.reEsserThreshHold);
    reEsserThreshHold.addListener(this);
    addAndMakeVisible (&reEsserThreshHold);
    
    reEsserMix.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    reEsserMix.setRange (0, 100, 1.0f);
    reEsserMix.setNumDecimalPlacesToDisplay(1);
    reEsserMix.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    reEsserMix.setPopupDisplayEnabled (true, false, this);
    reEsserMix.setTextValueSuffix (" Mix");
    reEsserMix.setValue(audioProcessor.reEsserMix);
    reEsserMix.addListener(this);
    addAndMakeVisible (&reEsserMix);
    
    sidechainGain.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    sidechainGain.setRange (-12, 12, 0.1f);
    sidechainGain.setNumDecimalPlacesToDisplay(1);
    sidechainGain.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    sidechainGain.setPopupDisplayEnabled (true, false, this);
    sidechainGain.setTextValueSuffix (" Gain factor");
    sidechainGain.setValue(audioProcessor.sidechainGain);
    sidechainGain.addListener(this);
    addAndMakeVisible (&sidechainGain);
    
    sidechainMix.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    sidechainMix.setRange (0, 100, 1.0f);
    sidechainMix.setNumDecimalPlacesToDisplay(1);
    sidechainMix.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    sidechainMix.setPopupDisplayEnabled (true, false, this);
    sidechainMix.setTextValueSuffix (" Mix");
    sidechainMix.setValue(audioProcessor.sidechainMix);
    sidechainMix.addListener(this);
    addAndMakeVisible (&sidechainMix);
    
    
    //========================================================
    // lfo 1
    LFO1freq.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO1freq.setRange (0.01, 20, 0.01f);
    LFO1freq.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO1freq.setPopupDisplayEnabled (true, false, this);
    LFO1freq.setTextValueSuffix (" Frequency");
    LFO1freq.setValue(audioProcessor.LFO1freq);
    LFO1freq.addListener(this);
    addAndMakeVisible (&LFO1freq);
    
    LFO1depth.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO1depth.setRange (0.0, 1.0, 0.01f);
    LFO1depth.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO1depth.setPopupDisplayEnabled (true, false, this);
    LFO1depth.setTextValueSuffix (" Depth");
    LFO1depth.setValue(audioProcessor.LFO1depth);
    LFO1depth.addListener(this);
    addAndMakeVisible (&LFO1depth);
    
    // lfo 2
    LFO2freq.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO2freq.setRange (0.01, 20, 0.01f);
    LFO2freq.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO2freq.setPopupDisplayEnabled (true, false, this);
    LFO2freq.setTextValueSuffix (" Frequency");
    LFO2freq.setValue(audioProcessor.LFO2freq);
    LFO2freq.addListener(this);
    addAndMakeVisible (&LFO2freq);
    
    LFO2depth.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO2depth.setRange (0.0, 1.0, 0.01f);
    LFO2depth.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO2depth.setPopupDisplayEnabled (true, false, this);
    LFO2depth.setTextValueSuffix (" Depth");
    LFO2depth.setValue(audioProcessor.LFO2depth);
    LFO2depth.addListener(this);
    addAndMakeVisible (&LFO2depth);
    
    // lfo 3
    LFO3freq.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO3freq.setRange (0.01, 20, 0.01f);
    LFO3freq.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO3freq.setPopupDisplayEnabled (true, false, this);
    LFO3freq.setTextValueSuffix (" Frequency");
    LFO3freq.setValue(audioProcessor.LFO3freq);
    LFO3freq.addListener(this);
    addAndMakeVisible (&LFO3freq);
    
    LFO3depth.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO3depth.setRange (0.0, 1.0, 0.01f);
    LFO3depth.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO3depth.setPopupDisplayEnabled (true, false, this);
    LFO3depth.setTextValueSuffix (" Depth");
    LFO3depth.setValue(audioProcessor.LFO3depth);
    LFO3depth.addListener(this);
    addAndMakeVisible (&LFO3depth);
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
    g.drawFittedText("Filters", 30, 10, 170, 20, juce::Justification::centred, 1);
    g.drawFittedText("Resonator", 300, 10, 170, 20, juce::Justification::centred, 1);
    g.drawFittedText("Spectral Glue", 30, getHeight() - 120, 170, 20, juce::Justification::centred, 1);
    g.drawFittedText("Sidechain", 300, getHeight() - 120, 170, 20, juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    lowShelfGain.setBounds(30, 30, 80, 80);
    highShelfGain.setBounds(120, 30, 80, 80);
    resonatorFrequency.setBounds(300, 30, 80, 80);
    resonatorDepth.setBounds(390, 30, 80, 80);
    reEsserThreshHold.setBounds(30, getHeight() - 100, 80, 80);
    reEsserMix.setBounds(120, getHeight() - 100, 80, 80);
    sidechainGain.setBounds(300, getHeight() - 100, 80, 80);
    sidechainMix.setBounds(390, getHeight() - 100, 80, 80);
    
    // mod sources
    LFO1freq.setBounds(50, 100, 45, 45);
    LFO1depth.setBounds(92, 100, 45, 45);
    LFO2freq.setBounds(150, 100, 45, 45);
    LFO2depth.setBounds(192, 100, 45, 45);
    LFO3freq.setBounds(320, 100, 45, 45);
    LFO3depth.setBounds(362, 100, 45, 45);
}

void NewProjectAudioProcessorEditor::sliderValueChanged(juce::Slider* slider){
    audioProcessor.lowShelfGain = lowShelfGain.getValue();
    audioProcessor.highShelfGain = highShelfGain.getValue();
    audioProcessor.resonatorFrequency = resonatorFrequency.getValue();
    audioProcessor.resonatorDepth = resonatorDepth.getValue();
    audioProcessor.reEsserThreshHold = reEsserThreshHold.getValue();
    audioProcessor.reEsserMix = reEsserMix.getValue();
    audioProcessor.sidechainGain = sidechainGain.getValue();
    audioProcessor.sidechainMix = sidechainMix.getValue();
    
    // lfo
    audioProcessor.LFO1freq = LFO1freq.getValue();
    audioProcessor.LFO1depth = LFO1depth.getValue();
    audioProcessor.LFO2freq = LFO2freq.getValue();
    audioProcessor.LFO2depth = LFO2depth.getValue();
    audioProcessor.LFO3freq = LFO3freq.getValue();
    audioProcessor.LFO3depth = LFO3depth.getValue();
}
