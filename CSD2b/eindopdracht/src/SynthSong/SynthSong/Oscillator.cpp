//
//  Oscillator.cpp
//  SynthSong
//
//  Created by Vincent Van den Broeck on 07/11/2023.
//

#include "Oscillator.hpp"
#include "audio_io.hpp"

Oscillator::Oscillator(double initFreq, double initAmp, double initPhase, int initOutputDevice){
    freq = initFreq;
    amp = initAmp;
    phase = initPhase;
    playState = false;
    x = 0; // sample index
    output_device = initOutputDevice;
};

void Oscillator::setFreq(double newFreq){
    freq = newFreq;
};

void Oscillator::setAmp(double newAmp){
    amp = newAmp;
};

void Oscillator::setPhase(double newPhase){
    phase = newPhase;
};

void Oscillator::start(){
    playState = true;
    audioCallback();
}

void Oscillator::stop(){
    playState = false;
}

Square::Square(double initFreq, double initAmp, double initPhase, double initDutyCycle, int initOutputDevice) : Oscillator(initFreq, initAmp, initPhase, initOutputDevice), dutyCycle(initDutyCycle) {
    dutyCycle = initDutyCycle;
}

Noise::Noise(double initAmp) : Oscillator(0.0, initAmp, 0.0) {
    amp = initAmp;
}

// audio callback
void Oscillator::audioCallback(){
    Audio_IO audiostream;
    audiostream.set_samplerate(SAMPLERATE);
    audiostream.set_nrofchannels(NROFCHANNELS);
    audiostream.set_framesperbuffer(FRAMESPERBUFFER);
    
    audiostream.initialise();
    audiostream.set_output_device(output_device);
    audiostream.start_server();
    
    do{
        // Fill a new buffer with samples
        for(bufptr=0; bufptr < FRAMESPERBUFFER*NROFCHANNELS; bufptr+=NROFCHANNELS)
        {
            // loop over the channels in one frame
            for(int channel=0;channel<NROFCHANNELS;channel++){
                samplebuffer[bufptr+channel] =
                (float)(amp * (sin((double)x * freq/SAMPLERATE * M_PI * 2.)));
            } // for channel
            x++; // advance to next time index
        } // for buffer index
        
        // send buffer to Portaudio
        audiostream.write(samplebuffer);
    } while(x < (SAMPLERATE * 3));
    
    audiostream.finalise();
    stop();
};
