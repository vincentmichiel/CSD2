#include <Bela.h>
#include <libraries/Fft/Fft.h>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
#include "MonoFilePlayer.h"
#include "FFTEffectExample.h"
#include "StereoDelay.h"

// Name of the sound file (in project folder)
std::string gFilename = "test.wav"; 

// Object that handles playing sound from a buffer
MonoFilePlayer gPlayer;

// FFT Object
FFTEffectExample * gFft;

StereoDelay * stereoDelay;

bool setup(BelaContext *context, void *userData)
{
	rt_printf("starting setup...\n");
	// Load the audio file
	if(!gPlayer.setup(gFilename)) {
    	rt_printf("	Error loading audio file '%s'\n", gFilename.c_str());
    	return false;
	}

	// Print some useful info
    rt_printf("Loaded the audio file '%s' with %d frames (%.1f seconds)\n", 
    			gFilename.c_str(), gPlayer.size(),
    			gPlayer.size() / context->audioSampleRate);
	
	// init fft object
	gFft = new FFTEffectExample();
    rt_printf("setup completed\n");
    
    stereoDelay = new StereoDelay(0.7792 * 2, 0.7792 * 4, context->audioSampleRate); // 0.7792 = 1 beat on 154 bpm
    
	return true;
}

void render(BelaContext *context, void *userData)
{
	for(unsigned int n = 0; n < context->audioFrames; n++) {
        // Read the next sample from the buffer
        float in = gPlayer.process();

        // MONO EFFECTS
        float fftIn = gFft->process(in);

		for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// STEREO EFFECTS
			float out = stereoDelay->process(fftIn, channel);
			audioWrite(context, n, channel, (out + in) * 0.5);
			
			// STEREO TICKS
			stereoDelay->tick(channel);
		}
		
		// MONO TICKS
	
	}
}

void cleanup(BelaContext *context, void *userData)
{
	delete gFft;
	delete stereoDelay;
}
