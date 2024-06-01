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
    return false;
}

bool NewProjectAudioProcessor::producesMidi() const
{
    return false;
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
    return false;
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;
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
    // init dsp modules
    setLatencySamples(reEsser[0].getLatencyInSamples());
    
    for(int channel = 0; channel < 2; channel++){
        lowShelfFilter[channel].setSampleRate(sampleRate);
        lowShelfFilter[channel].setAffectsLowEnd(true);
        lowShelfFilter[channel].prepare();
        lowShelfFilter[channel].reset();
        
        highShelfFilter[channel].setSampleRate(sampleRate);
        highShelfFilter[channel].prepare();
        highShelfFilter[channel].reset();
        
        resonator[channel].setSampleRate(sampleRate);
        resonator[channel].prepare(resonatorFrequency, 1.0, sampleRate);
        resonator[channel].reset();
        
        reEsser[channel].setSampleRate(sampleRate);
        reEsser[channel].reset();
    }
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any spare memory
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
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
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        // set parameters
        lowShelfFilter[channel].setDrive(lowShelfGain);
        highShelfFilter[channel].setDrive(highShelfGain);
        
        resonator[channel].lfo->setFrequency(resonatorFrequency);
        resonator[channel].setDepth(resonatorDepth);
        
        reEsser[channel].setThreshHold(reEsserThreshHold);
        reEsser[channel].setCenterFrequency(6000);
        reEsser[channel].setBandWidth(0.98);
        
        // select current channel
        float* channelS = buffer.getWritePointer(channel);
        
        // loop through channel buffer
        for (int sample = 0; sample < numSamples; ++sample) {
            // resonator fft
            if(resonatorDepth > 0){
                resonator[channel].spectrumAnalyser.processSample(resonator[channel].lfo->getSample(), false);
                resonator[channel].lfo->tick();
            }
            
            float input = channelS[sample];
            
            // shelf filters
            input = lowShelfFilter[channel].processSample(input, false);
            input = highShelfFilter[channel].processSample(input, false);
            
            // resonator
            if(resonatorDepth > 0){
                input = resonator[channel].processSample(input, false);
            }
            
            // spectral glue
            if(reEsserMix > 0 && reEsserThreshHold < 1)
            {
                float pre = input;
                // processing -> wet signal gain correction -> gain correction
                input = reEsser[channel].processSample(input, false) * (reEsserMix / 100) * (0.08 + reEsserThreshHold * 0.8);
                // dry signal
                input += (pre * (1.0f - (reEsserMix / 100)));
            }
            
            channelS[sample] = input;
        }
    }
}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream (destData, true).writeFloat (lowShelfGain);
    juce::MemoryOutputStream (destData, true).writeFloat (highShelfGain);
    juce::MemoryOutputStream (destData, true).writeFloat (resonatorFrequency);
    juce::MemoryOutputStream (destData, true).writeFloat (resonatorDepth);
    juce::MemoryOutputStream (destData, true).writeFloat (reEsserThreshHold);
    juce::MemoryOutputStream (destData, true).writeFloat (reEsserMix);
    juce::MemoryOutputStream (destData, true).writeFloat (sidechainGain);
    juce::MemoryOutputStream (destData, true).writeFloat (sidechainMix);
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    lowShelfGain = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    highShelfGain = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    resonatorFrequency = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    resonatorDepth = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    reEsserThreshHold = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    reEsserMix = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    sidechainGain = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    sidechainMix = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
