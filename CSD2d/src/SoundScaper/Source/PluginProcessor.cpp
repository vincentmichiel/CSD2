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
        resonator[channel].spectrumAnalyser.reset();
        resonator[channel].prepare(resonatorFrequency, 1.0, sampleRate);
        resonator[channel].reset();
        
        reEsser[channel].setSampleRate(sampleRate);
        reEsser[channel].reset();
        
        chordifyer[channel].setSampleRate(sampleRate);
        chordifyer[channel].sidechainAnalyser.setSampleRate(sampleRate);
        chordifyer[channel].reset();
        chordifyer[channel].sidechainAnalyser.reset();
        
        // mod sources
        LFO1[channel].setSamplerate(sampleRate);
        LFO1[channel].setFrequency(LFO1freq);
        LFO1[channel].setAmplitude(LFO1depth);
        LFO2[channel].setSamplerate(sampleRate);
        LFO2[channel].setFrequency(LFO2freq);
        LFO2[channel].setAmplitude(LFO2depth);
        LFO3[channel].setSamplerate(sampleRate);
        LFO3[channel].setFrequency(LFO3freq);
        LFO3[channel].setAmplitude(LFO3depth);
    }
}

void NewProjectAudioProcessor::releaseResources()
{
    for(int channel = 0; channel < 2; channel++){
        lowShelfFilter[channel].reset();
        highShelfFilter[channel].reset();
        resonator[channel].reset();
        resonator[channel].spectrumAnalyser.reset();
        resonator[channel].lfo->setAmplitude(0);
        reEsser[channel].reset();
        chordifyer[channel].reset();
        chordifyer[channel].sidechainAnalyser.reset();
    }
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
    
    auto mainBuffer = getBusBuffer(buffer, true, 0);
    auto sidechainBuffer = getBusBuffer(buffer, true, 1);
    
    for (int channel = 0; channel < 2; ++channel)
    {
        // set parameters
        // mod sources
        LFO1[channel].setFrequency(LFO1freq);
        if(LFO1phase != LFO1[channel].getPhaseOffset()) LFO1[channel].setPhase(LFO1phase);
        LFO1[channel].setAmplitude(LFO1depth);
        LFO2[channel].setFrequency(LFO2freq);
        if(LFO2phase != LFO2[channel].getPhaseOffset()) LFO2[channel].setPhase(LFO2phase);
        LFO2[channel].setAmplitude(LFO2depth);
        LFO3[channel].setFrequency(LFO3freq);
        if(LFO3phase != LFO3[channel].getPhaseOffset()) LFO3[channel].setPhase(LFO3phase);
        LFO3[channel].setAmplitude(LFO3depth);
        
        // DSP modules
        lowShelfFilter[channel].setDrive(lowShelfGain + (LFO1[channel].getSample() * (12)));
        highShelfFilter[channel].setDrive(highShelfGain + (LFO2[channel].getSample() * (12)));
        
        resonator[channel].lfo->setFrequency(resonatorFrequency + (LFO3[channel].getSample() * (resonatorFrequency/10)));
        resonator[channel].setDepth(resonatorDepth);
        resonator[channel].lfo->setAmplitude(1);
        
        reEsser[channel].setThreshHold(reEsserThreshHold);
        reEsser[channel].setCenterFrequency(6000);
        reEsser[channel].setBandWidth(0.98);
        
        chordifyer[channel].setSidechainGain(sidechainGain);
    
        
        // select current channel
        float* channelS = mainBuffer.getWritePointer(channel);
        
        // loop through channel buffer
        for (int sample = 0; sample < numSamples; ++sample) {
            // resonator fft
            if(resonatorDepth > 0){
                resonator[channel].spectrumAnalyser.processSample(resonator[channel].lfo->getSample(), false);
                resonator[channel].lfo->tick();
            }
            
            float input = channelS[sample];
            
            // shelf filters
            if(lowShelfGain != 0){
                input = lowShelfFilter[channel].processSample(input, false);
            }
            if(highShelfGain != 0){
                input = highShelfFilter[channel].processSample(input, false);
            }
            
            // resonator
            if(resonatorDepth > 0){
                input = resonator[channel].processSample(input, false);
            }
            
            // spectral glue
            if(reEsserMix > 0 && reEsserThreshHold < 1)
            {
                float pre = input;
                // processing -> wet signal gain correction -> gain correction
                input = reEsser[channel].processSample(input, false) * (reEsserMix / 100.0f) * (0.08f + reEsserThreshHold * 0.8f);
                // dry signal
                input += (pre * (1.0f - (reEsserMix / 100.0f)));
            }
            
            // sidechain processing
            // analyse sidechain channel
            if(totalNumInputChannels > 2){
                sidechainBuffer.getWritePointer(channel)[sample] = chordifyer[channel].sidechainAnalyser.processSample(sidechainBuffer.getWritePointer(channel)[sample], false);
            }
            
            if(sidechainMix > 0){
                float pre = input;
                // processing -> wet signal gain correction -> gain correction
                input = chordifyer[channel].processSample(input, false) * (sidechainMix / 100.0f);
                // dry signal
                input += (pre * (1.0f - (sidechainMix / 100.0f)));
            }
            
            channelS[sample] = input;
            tick(channel);
        }
    }
}

void NewProjectAudioProcessor::tick(int channel){
    LFO1[channel].tick();
    LFO2[channel].tick();
    LFO3[channel].tick();
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
