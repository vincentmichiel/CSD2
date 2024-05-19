/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                  .withInput  ("Sidechain", juce::AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                  )
#endif
{
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

//==============================================================================
const juce::String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    setLatencySamples(chordifyer[0].getLatencyInSamples());
    
    chordifyer[0].setSampleRate(sampleRate);
    chordifyer[1].setSampleRate(sampleRate);
    chordifyer[0].sidechainAnalyser.setSampleRate(sampleRate);
    chordifyer[1].sidechainAnalyser.setSampleRate(sampleRate);
    
    chordifyer[0].reset();
    chordifyer[1].reset();
    chordifyer[0].sidechainAnalyser.reset();
    chordifyer[1].sidechainAnalyser.reset();
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
#endif

void NewProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto numSamples = buffer.getNumSamples();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    auto mainBuffer = getBusBuffer(buffer, true, 0);
    auto sidechainBuffer = getBusBuffer(buffer, true, 1);
    
    for (int channel = 0; channel < 2; ++channel)
    {
        // select current channel
        float* channelS = mainBuffer.getWritePointer(channel);
        
        // loop through channel buffer
        for (int sample = 0; sample < numSamples; ++sample) {
            // analyse sidechain channel
            if(totalNumInputChannels > 2){
                sidechainBuffer.getWritePointer(channel)[sample] = chordifyer[channel].sidechainAnalyser.processSample(sidechainBuffer.getWritePointer(channel)[sample], false);
            }
            
            float input = channelS[sample];
            input = chordifyer[channel].processSample(input, false);
            channelS[sample] = input;
        }
    }
    
}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // store data
    juce::MemoryOutputStream (destData, true).writeFloat (threshHold);
    juce::MemoryOutputStream (destData, true).writeFloat (centerFrequency);
    juce::MemoryOutputStream (destData, true).writeFloat (bandWidth);
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // load data
    threshHold = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    centerFrequency = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    bandWidth = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
