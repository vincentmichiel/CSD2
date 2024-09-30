#include <Bela.h>
#include <libraries/Fft/Fft.h>
#include "MonoFilePlayer.h"
#include "FFTWrapper.h"

// init sound file and playing object
std::string gFilename = "test.wav"; 
MonoFilePlayer gPlayer;

// init fft processor
FFTWrapper fftProcessor;

bool setup(BelaContext *context, void *userData)
{
	// Load the audio file
	if(!gPlayer.setup(gFilename)) {
    	rt_printf("Error loading audio file '%s'\n", gFilename.c_str());
    	return false;
	}

	// Print some useful info
    rt_printf("Loaded the audio file '%s' with %d frames (%.1f seconds)\n", 
    			gFilename.c_str(), gPlayer.size(),
    			gPlayer.size() / context->audioSampleRate);
    			
	return true;
}

void render(BelaContext *context, void *userData)
{
	for(unsigned int n = 0; n < context->audioFrames; n++) {
		 // Read the next sample from the buffer
        float in = gPlayer.process();

		in = fftProcessor.process(in);
		float out = in * 0.2;

		for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			audioWrite(context, n, channel, out);
		}
	}
}

void cleanup(BelaContext *context, void *userData)
{

}