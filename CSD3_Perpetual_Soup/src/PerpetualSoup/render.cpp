#include <Bela.h>
#include <libraries/Fft/Fft.h>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
#include "MonoFilePlayer.h"
#include "FFTEffectExample.h"

// Name of the sound file (in project folder)
std::string gFilename = "test.wav"; 

// Object that handles playing sound from a buffer
MonoFilePlayer gPlayer;

// FFT Object
FFTEffectExample * gFft;

bool setup(BelaContext *context, void *userData)
{
	rt_printf("starting setup...\n");
	// Load the audio file
	if(!gPlayer.setup(gFilename)) {
    	rt_printf("Error loading audio file '%s'\n", gFilename.c_str());
    	return false;
	}

	// Print some useful info
    rt_printf("Loaded the audio file '%s' with %d frames (%.1f seconds)\n", 
    			gFilename.c_str(), gPlayer.size(),
    			gPlayer.size() / context->audioSampleRate);
	
	// init fft object
	gFft = new FFTEffectExample();
    rt_printf("setup completed\n");
	return true;
}

void render(BelaContext *context, void *userData)
{
	for(unsigned int n = 0; n < context->audioFrames; n++) {
        // Read the next sample from the buffer
        float in = gPlayer.process();
        
        // process input
		float out = gFft->process(in);

		// Write the audio to the output
		for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			audioWrite(context, n, channel, out);
		}
	}
}

void cleanup(BelaContext *context, void *userData)
{
	delete gFft;
}
