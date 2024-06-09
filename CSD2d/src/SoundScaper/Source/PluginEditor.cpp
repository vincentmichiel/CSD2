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
    setSize (510, 375);
    
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
    
    LFO1phase.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO1phase.setRange (0.0, 1.0, 0.01f);
    LFO1phase.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO1phase.setPopupDisplayEnabled (true, false, this);
    LFO1phase.setTextValueSuffix (" Phase");
    LFO1phase.setValue(audioProcessor.LFO1phase);
    LFO1phase.addListener(this);
    addAndMakeVisible (&LFO1phase);
    
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
    
    LFO2phase.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO2phase.setRange (0.0, 1.0, 0.01f);
    LFO2phase.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO2phase.setPopupDisplayEnabled (true, false, this);
    LFO2phase.setTextValueSuffix (" Phase");
    LFO2phase.setValue(audioProcessor.LFO2phase);
    LFO2phase.addListener(this);
    addAndMakeVisible (&LFO2phase);
    
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
    
    LFO3phase.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO3phase.setRange (0.0, 1.0, 0.01f);
    LFO3phase.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO3phase.setPopupDisplayEnabled (true, false, this);
    LFO3phase.setTextValueSuffix (" Phase");
    LFO3phase.setValue(audioProcessor.LFO3phase);
    LFO3phase.addListener(this);
    addAndMakeVisible (&LFO3phase);
    
    LFO3depth.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO3depth.setRange (0.0, 1.0, 0.01f);
    LFO3depth.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO3depth.setPopupDisplayEnabled (true, false, this);
    LFO3depth.setTextValueSuffix (" Depth");
    LFO3depth.setValue(audioProcessor.LFO3depth);
    LFO3depth.addListener(this);
    addAndMakeVisible (&LFO3depth);
    
    // lfo 4
    LFO4freq.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO4freq.setRange (0.01, 20, 0.01f);
    LFO4freq.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO4freq.setPopupDisplayEnabled (true, false, this);
    LFO4freq.setTextValueSuffix (" Frequency");
    LFO4freq.setValue(audioProcessor.LFO4freq);
    LFO4freq.addListener(this);
    addAndMakeVisible (&LFO4freq);
    
    LFO4phase.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO4phase.setRange (0.0, 1.0, 0.01f);
    LFO4phase.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO4phase.setPopupDisplayEnabled (true, false, this);
    LFO4phase.setTextValueSuffix (" Phase");
    LFO4phase.setValue(audioProcessor.LFO4phase);
    LFO4phase.addListener(this);
    addAndMakeVisible (&LFO4phase);
    
    LFO4depth.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO4depth.setRange (0.0, 1.0, 0.01f);
    LFO4depth.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO4depth.setPopupDisplayEnabled (true, false, this);
    LFO4depth.setTextValueSuffix (" Depth");
    LFO4depth.setValue(audioProcessor.LFO4depth);
    LFO4depth.addListener(this);
    addAndMakeVisible (&LFO4depth);
    
    // lfo 5
    LFO5freq.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO5freq.setRange (0.01, 20, 0.01f);
    LFO5freq.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO5freq.setPopupDisplayEnabled (true, false, this);
    LFO5freq.setTextValueSuffix (" Frequency");
    LFO5freq.setValue(audioProcessor.LFO5freq);
    LFO5freq.addListener(this);
    addAndMakeVisible (&LFO5freq);
    
    LFO5phase.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO5phase.setRange (0.0, 1.0, 0.01f);
    LFO5phase.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO5phase.setPopupDisplayEnabled (true, false, this);
    LFO5phase.setTextValueSuffix (" Phase");
    LFO5phase.setValue(audioProcessor.LFO5phase);
    LFO5phase.addListener(this);
    addAndMakeVisible (&LFO5phase);
    
    LFO5depth.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO5depth.setRange (0.0, 1.0, 0.01f);
    LFO5depth.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO5depth.setPopupDisplayEnabled (true, false, this);
    LFO5depth.setTextValueSuffix (" Depth");
    LFO5depth.setValue(audioProcessor.LFO5depth);
    LFO5depth.addListener(this);
    addAndMakeVisible (&LFO5depth);
    
    // lfo 6
    LFO6freq.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO6freq.setRange (0.01, 20, 0.01f);
    LFO6freq.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO6freq.setPopupDisplayEnabled (true, false, this);
    LFO6freq.setTextValueSuffix (" Frequency");
    LFO6freq.setValue(audioProcessor.LFO6freq);
    LFO6freq.addListener(this);
    addAndMakeVisible (&LFO6freq);
    
    LFO6phase.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO6phase.setRange (0.0, 1.0, 0.01f);
    LFO6phase.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO6phase.setPopupDisplayEnabled (true, false, this);
    LFO6phase.setTextValueSuffix (" Phase");
    LFO6phase.setValue(audioProcessor.LFO6phase);
    LFO6phase.addListener(this);
    addAndMakeVisible (&LFO6phase);
    
    LFO6depth.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO6depth.setRange (0.0, 1.0, 0.01f);
    LFO6depth.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO6depth.setPopupDisplayEnabled (true, false, this);
    LFO6depth.setTextValueSuffix (" Depth");
    LFO6depth.setValue(audioProcessor.LFO6depth);
    LFO6depth.addListener(this);
    addAndMakeVisible (&LFO6depth);
    
    // lfo 7
    LFO7freq.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO7freq.setRange (0.01, 20, 0.01f);
    LFO7freq.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO7freq.setPopupDisplayEnabled (true, false, this);
    LFO7freq.setTextValueSuffix (" Frequency");
    LFO7freq.setValue(audioProcessor.LFO7freq);
    LFO7freq.addListener(this);
    addAndMakeVisible (&LFO7freq);
    
    LFO7phase.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO7phase.setRange (0.0, 1.0, 0.01f);
    LFO7phase.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO7phase.setPopupDisplayEnabled (true, false, this);
    LFO7phase.setTextValueSuffix (" Phase");
    LFO7phase.setValue(audioProcessor.LFO7phase);
    LFO7phase.addListener(this);
    addAndMakeVisible (&LFO7phase);
    
    LFO7depth.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO7depth.setRange (0.0, 1.0, 0.01f);
    LFO7depth.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO7depth.setPopupDisplayEnabled (true, false, this);
    LFO7depth.setTextValueSuffix (" Depth");
    LFO7depth.setValue(audioProcessor.LFO7depth);
    LFO7depth.addListener(this);
    addAndMakeVisible (&LFO7depth);
    
    // lfo 8
    LFO8freq.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO8freq.setRange (0.01, 20, 0.01f);
    LFO8freq.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO8freq.setPopupDisplayEnabled (true, false, this);
    LFO8freq.setTextValueSuffix (" Frequency");
    LFO8freq.setValue(audioProcessor.LFO8freq);
    LFO8freq.addListener(this);
    addAndMakeVisible (&LFO8freq);
    
    LFO8phase.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO8phase.setRange (0.0, 1.0, 0.01f);
    LFO8phase.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO8phase.setPopupDisplayEnabled (true, false, this);
    LFO8phase.setTextValueSuffix (" Phase");
    LFO8phase.setValue(audioProcessor.LFO8phase);
    LFO8phase.addListener(this);
    addAndMakeVisible (&LFO8phase);
    
    LFO8depth.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    LFO8depth.setRange (0.0, 1.0, 0.01f);
    LFO8depth.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    LFO8depth.setPopupDisplayEnabled (true, false, this);
    LFO8depth.setTextValueSuffix (" Depth");
    LFO8depth.setValue(audioProcessor.LFO8depth);
    LFO8depth.addListener(this);
    addAndMakeVisible (&LFO8depth);
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
    g.drawFittedText("Spectral Glue", 30, getHeight() - 150, 170, 20, juce::Justification::centred, 1);
    g.drawFittedText("Sidechain", 300, getHeight() - 150, 170, 20, juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    lowShelfGain.setBounds(30, 25, 80, 80);
    highShelfGain.setBounds(120, 25, 80, 80);
    resonatorFrequency.setBounds(300, 25, 80, 80);
    resonatorDepth.setBounds(390, 25, 80, 80);
    reEsserThreshHold.setBounds(30, getHeight() - 135, 80, 80);
    reEsserMix.setBounds(120, getHeight() - 135, 80, 80);
    sidechainGain.setBounds(300, getHeight() - 135, 80, 80);
    sidechainMix.setBounds(390, getHeight() - 135, 80, 80);
    
    // mod sources
    LFO1freq.setBounds(40, 95, 45, 45);
    LFO1phase.setBounds(55, 115, 45, 45);
    LFO1depth.setBounds(80, 95, 45, 45);
    LFO2freq.setBounds(130, 95, 45, 45);
    LFO2phase.setBounds(145, 115, 45, 45);
    LFO2depth.setBounds(170, 95, 45, 45);
    LFO3freq.setBounds(310, 95, 45, 45);
    LFO3phase.setBounds(325, 115, 45, 45);
    LFO3depth.setBounds(350, 95, 45, 45);
    LFO4freq.setBounds(400, 95, 45, 45);
    LFO4phase.setBounds(415, 115, 45, 45);
    LFO4depth.setBounds(440, 95, 45, 45);
    
    LFO5freq.setBounds(40, getHeight() - 65, 45, 45);
    LFO5phase.setBounds(55, getHeight() - 45, 45, 45);
    LFO5depth.setBounds(80, getHeight() - 65, 45, 45);
    LFO6freq.setBounds(130, getHeight() - 65, 45, 45);
    LFO6phase.setBounds(145, getHeight() - 45, 45, 45);
    LFO6depth.setBounds(170, getHeight() - 65, 45, 45);
    LFO7freq.setBounds(310, getHeight() - 65, 45, 45);
    LFO7phase.setBounds(325, getHeight() - 45, 45, 45);
    LFO7depth.setBounds(350, getHeight() - 65, 45, 45);
    LFO8freq.setBounds(400, getHeight() - 65, 45, 45);
    LFO8phase.setBounds(415, getHeight() - 45, 45, 45);
    LFO8depth.setBounds(440, getHeight() - 65, 45, 45);
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
    audioProcessor.LFO1phase = LFO1phase.getValue();
    audioProcessor.LFO1depth = LFO1depth.getValue();
    audioProcessor.LFO2freq = LFO2freq.getValue();
    audioProcessor.LFO2phase = LFO2phase.getValue();
    audioProcessor.LFO2depth = LFO2depth.getValue();
    audioProcessor.LFO3freq = LFO3freq.getValue();
    audioProcessor.LFO3phase = LFO3phase.getValue();
    audioProcessor.LFO3depth = LFO3depth.getValue();
    audioProcessor.LFO4freq = LFO4freq.getValue();
    audioProcessor.LFO4phase = LFO4phase.getValue();
    audioProcessor.LFO4depth = LFO4depth.getValue();
    
    audioProcessor.LFO5freq = LFO5freq.getValue();
    audioProcessor.LFO5phase = LFO5phase.getValue();
    audioProcessor.LFO5depth = LFO5depth.getValue();
    audioProcessor.LFO6freq = LFO6freq.getValue();
    audioProcessor.LFO6phase = LFO6phase.getValue();
    audioProcessor.LFO6depth = LFO6depth.getValue();
    audioProcessor.LFO7freq = LFO7freq.getValue();
    audioProcessor.LFO7phase = LFO7phase.getValue();
    audioProcessor.LFO7depth = LFO7depth.getValue();
    audioProcessor.LFO8freq = LFO8freq.getValue();
    audioProcessor.LFO8phase = LFO8phase.getValue();
    audioProcessor.LFO8depth = LFO8depth.getValue();
}
