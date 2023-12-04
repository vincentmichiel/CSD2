#include "jack_module.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include "Oscillator.hpp"


/*
 * NOTE: jack2 needs to be installed
 * jackd invokes the JACK audio server daemon
 * https://github.com/jackaudio/jackaudio.github.com/wiki/jackd(1)
 * on mac, you can start the jack audio server daemon in the terminal:
 * jackd -d coreaudio
 */

class CustomCallback : public AudioCallback {
public:
    void prepare (int rate) override {
        samplerate = (float) rate;
        sine.setSamplerate(samplerate);
    }

    // audio callback function
    void process (AudioBuffer buffer) override {
        // open text file
        std::ofstream outfile;
        outfile.open("waveform.txt");
        
        for (int i = 0; i < buffer.numFrames; ++i) {
            // calculate sample and write to audio buffer
            float sample = sine.getSample();
            buffer.outputChannels[0][i] = sample;
            
            // write to text file
            outfile << sine.getPhase() << ":" << sample << std::endl;
            
            sine.tick();
        }
        // close text file
        outfile.close();
    }

private:
    float samplerate = 44100;
    Sine sine = Sine(440, 1, samplerate);
};

// ================================================================================

int main() {
    CustomCallback callback = CustomCallback {};
    JackModule jackModule = JackModule { callback };
    jackModule.init (0, 1);
    
    // clear plot file
    std::ofstream ofs;
    ofs.open("waveform.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    bool running = true;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
        }
    }
    return 0;
}
