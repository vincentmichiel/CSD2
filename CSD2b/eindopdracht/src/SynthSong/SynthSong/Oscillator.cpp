//
//  Oscillator.cpp
//  SynthSong
//
//  Created by Vincent Van den Broeck on 07/11/2023.
//

#include "Oscillator.hpp"
#include "audio_io.hpp"

Oscillator::Oscillator(double initFreq, double initAmp, int initOutputDevice){
    freq = initFreq;
    amp = initAmp;
    playState = false;
    x = 0; // sample index
    output_device = initOutputDevice;
    
    // start audio stream
    audiostream.set_samplerate(SAMPLERATE);
    audiostream.set_nrofchannels(NROFCHANNELS);
    audiostream.set_framesperbuffer(FRAMESPERBUFFER);
    
    audiostream.initialise();
    audiostream.set_output_device(output_device);
    audiostream.start_server();
};

Oscillator::~Oscillator(){
    // close audio thread if open
    stop();
    // stop audio stream
    audiostream.finalise();
};

void Oscillator::setFreq(double newFreq){
    freq = newFreq;
};

void Oscillator::setAmp(double newAmp){
    amp = newAmp;
};

double Oscillator::getAmp(){
    return amp;
};

void Oscillator::start(){
    // create new thread
    audioThread = std::thread([this] {
        playState = true;
        audioCallback();
    });
    // sleep main thread to give the audio thread a moment to start
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
};

void Oscillator::stop(){
    playState = false;
    
    // close audio thread
    if (audioThread.joinable()) {
        audioThread.join();  // Wait for the audio thread to complete
    }
};

Square::Square(double initFreq, double initAmp, double initDutyCycle, int initOutputDevice) : Oscillator(initFreq, initAmp, initOutputDevice), dutyCycle(initDutyCycle) {
    dutyCycle = initDutyCycle;
};

Noise::Noise(double initAmp) : Oscillator(0.0, initAmp, 0) {
    amp = initAmp;
    randomEngine = std::default_random_engine(std::random_device()());
    distribution = std::uniform_real_distribution<float>(-1.0, 1.0);
}

// audio callback and sound generation
float Oscillator::sampleGenerator(unsigned long timeIndex) {
    // sine wave as default
    return (float)(amp * (sin((double)timeIndex * freq/SAMPLERATE * M_PI * 2.)));
};

float Sine::sampleGenerator(unsigned long timeIndex){
    // sine wave
    return (float)(amp * (sin((double)timeIndex * freq/SAMPLERATE * M_PI * 2.)));
};

float Square::sampleGenerator(unsigned long timeIndex){
    // square wave
    double t = (double)timeIndex / SAMPLERATE; // time index in seconds
    double period = 1.0 / freq;
    double halfPeriod = period / 2;
    double phase = fmod(t, period);
    
    return (float)(amp * (phase < (halfPeriod * dutyCycle) ? 1.0 : -1.0));
};

float Triangle::sampleGenerator(unsigned long timeIndex) {
    // Triangle wave
        double t = (double)timeIndex / SAMPLERATE; // time index in seconds
        double period = 1.0 / freq;
        double phase = fmod(t, period); // t % period

        double amplitude = 2.0 * amp / period;
        double triangleValue = 0.0;

        if (phase < (period / 2.0)) { // rising part of wave
            triangleValue = amplitude * phase - amp;
        } else { // falling part of wave
            triangleValue = -amplitude * (phase - period) + amp;
        }

        return (float)triangleValue;
};

float Noise::sampleGenerator(unsigned long timeIndex){
    // random for noise
    return amp * distribution(randomEngine);
};

void Oscillator::audioCallback(){
    do {
        // Fill a new buffer with samples
        for(bufptr=0; bufptr < FRAMESPERBUFFER*NROFCHANNELS; bufptr+=NROFCHANNELS)
        {
            // loop over the channels in one frame
            for(int channel=0;channel<NROFCHANNELS;channel++){
                samplebuffer[bufptr+channel] = sampleGenerator(x);
            } // for channel
            x++; // advance to next time index
        } // for buffer index
        
        // send buffer to Portaudio
        audiostream.write(samplebuffer);
    } while (playState);
    // reset sample buffer and time index
    x = 0;
    for (int i = 0; i < FRAMESPERBUFFER * NROFCHANNELS; i++) {
        samplebuffer[i] = 0.0f;
    }
};
