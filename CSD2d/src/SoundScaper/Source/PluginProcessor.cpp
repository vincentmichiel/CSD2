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
        LFO4[channel].setSamplerate(sampleRate);
        LFO4[channel].setFrequency(LFO4freq);
        LFO4[channel].setAmplitude(LFO4depth);
        
        LFO5[channel].setSamplerate(sampleRate);
        LFO5[channel].setFrequency(LFO5freq);
        LFO5[channel].setAmplitude(LFO5depth);
        LFO6[channel].setSamplerate(sampleRate);
        LFO6[channel].setFrequency(LFO6freq);
        LFO6[channel].setAmplitude(LFO6depth);
        LFO7[channel].setSamplerate(sampleRate);
        LFO7[channel].setFrequency(LFO7freq);
        LFO7[channel].setAmplitude(LFO7depth);
        LFO8[channel].setSamplerate(sampleRate);
        LFO8[channel].setFrequency(LFO8freq);
        LFO8[channel].setAmplitude(LFO8depth);
    }
}

void NewProjectAudioProcessor::releaseResources()
{
    for(int channel = 0; channel < 2; channel++){
        lowShelfFilter[channel].reset();
        highShelfFilter[channel].reset();
        resonator[channel].reset();
        resonator[channel].spectrumAnalyser.reset();
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
        LFO4[channel].setFrequency(LFO4freq);
        if(LFO4phase != LFO4[channel].getPhaseOffset()) LFO4[channel].setPhase(LFO4phase);
        LFO4[channel].setAmplitude(LFO4depth);
        
        LFO5[channel].setFrequency(LFO5freq);
        if(LFO5phase != LFO5[channel].getPhaseOffset()) LFO5[channel].setPhase(LFO5phase);
        LFO5[channel].setAmplitude(LFO5depth);
        LFO6[channel].setFrequency(LFO6freq);
        if(LFO6phase != LFO6[channel].getPhaseOffset()) LFO6[channel].setPhase(LFO6phase);
        LFO6[channel].setAmplitude(LFO6depth);
        LFO7[channel].setFrequency(LFO7freq);
        if(LFO7phase != LFO7[channel].getPhaseOffset()) LFO7[channel].setPhase(LFO7phase);
        LFO7[channel].setAmplitude(LFO7depth);
        LFO8[channel].setFrequency(LFO8freq);
        if(LFO8phase != LFO8[channel].getPhaseOffset()) LFO8[channel].setPhase(LFO8phase);
        LFO8[channel].setAmplitude(LFO8depth);
        
        // DSP modules
        lowShelfFilter[channel].setDrive(lowShelfGain + (LFO1[channel].getSample() * (12)));
        highShelfFilter[channel].setDrive(highShelfGain + (LFO2[channel].getSample() * (12)));
        
        resonator[channel].lfo->setFrequency(resonatorFrequency + (LFO3[channel].getSample() * (resonatorFrequency/10)));
        float resDepth = resonatorDepth + LFO4[channel].getSample();
        if(resDepth > 1) resDepth = 1;
        if(resDepth < 0) resDepth = 0;
        resonator[channel].setDepth(resDepth);
        
        float moddedThreshHold = reEsserThreshHold + LFO5[channel].getSample();
        if(moddedThreshHold > 1) moddedThreshHold = 1;
        if(moddedThreshHold < 0) moddedThreshHold = 0;
        reEsser[channel].setThreshHold(moddedThreshHold);
        reEsser[channel].setCenterFrequency(6000);
        reEsser[channel].setBandWidth(0.98);
        
        chordifyer[channel].setSidechainGain(sidechainGain + (LFO7[channel].getSample() * (12)));
    
        
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
                float moddedReEsserMix = (reEsserMix / 100.0f) + LFO6[channel].getSample();
                if(moddedReEsserMix > 1) {
                    moddedReEsserMix = 1;
                } else if(moddedReEsserMix < 0){
                    moddedReEsserMix = 0;
                }
                input = reEsser[channel].processSample(input, false) * moddedReEsserMix * (0.08f + reEsserThreshHold * 0.8f);
                // dry signal
                input += (pre * (1.0f - moddedReEsserMix));
            }
            
            // sidechain processing
            // analyse sidechain channel
            if(totalNumInputChannels > 2){
                sidechainBuffer.getWritePointer(channel)[sample] = chordifyer[channel].sidechainAnalyser.processSample(sidechainBuffer.getWritePointer(channel)[sample], false);
            }
            
            if(sidechainMix > 0){
                float pre = input;
                // processing -> wet signal gain correction -> gain correction
                float moddedSidechainMix = (sidechainMix / 100.0f) + LFO8[channel].getSample();
                if(moddedSidechainMix > 1) {
                    moddedSidechainMix = 1;
                } else if(moddedSidechainMix < 0){
                    moddedSidechainMix = 0;
                }
                input = chordifyer[channel].processSample(input, false) * moddedSidechainMix;
                // dry signal
                input += (pre * (1.0f - moddedSidechainMix));
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
    LFO4[channel].tick();
    
    LFO5[channel].tick();
    LFO6[channel].tick();
    LFO7[channel].tick();
    LFO8[channel].tick();
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
    
    // mod sources
    juce::MemoryOutputStream (destData, true).writeFloat (LFO1freq);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO1phase);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO1depth);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO2freq);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO2phase);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO2depth);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO3freq);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO3phase);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO3depth);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO4freq);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO4phase);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO4depth);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO5freq);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO5phase);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO5depth);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO6freq);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO6phase);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO6depth);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO7freq);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO7phase);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO7depth);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO8freq);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO8phase);
    juce::MemoryOutputStream (destData, true).writeFloat (LFO8depth);
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
    
    // mod sources
    LFO1freq = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO1phase = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO1depth = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO2freq = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO2phase = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO2depth = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO3freq = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO3phase = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO3depth = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO4freq = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO4phase = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO4depth = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO5freq = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO5phase = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO5depth = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO6freq = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO6phase = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO6depth = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO7freq = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO7phase = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO7depth = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO8freq = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO8phase = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    LFO8depth = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
