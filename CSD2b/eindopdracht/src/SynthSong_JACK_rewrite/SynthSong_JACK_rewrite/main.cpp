#include "jack_module.h"
#include <cmath>
#include <iostream>
#include <fstream>


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
    }

    // ___QUESTION___
    // Why do we need to 'wrap' phase to 0 after > 1 and thereby keep it between the range [0,1]?

    // audio callback function
    void process (AudioBuffer buffer) override {
        // open text file
        std::ofstream outfile;
        outfile.open("waveform.txt");
        
        for (int i = 0; i < buffer.numFrames; ++i) {
            // calculate sample
            float sample = sin (phase * pi * 2.0f);
            // write sample to buffer at channel 0
            buffer.outputChannels[0][i] = sample;
            phase += frequency / samplerate;
            if (phase > 1.0f) {
              phase -= 1.0f;
            }
            // write to text file
            outfile << phase << ":" << sample << std::endl;
        }
        // close text file
        outfile.close();
    }

private:
    const float pi = acos (-1);  //atan(1) * 4; <-- vak van Pieter.
    float phase = 0;
    float frequency = 440;
    float samplerate;
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
