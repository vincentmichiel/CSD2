#include <Bela.h>
#include <libraries/Fft/Fft.h>
#include <libraries/Scope/Scope.h>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>

class FFTWrapper {
	private:
	Fft gFft;							// FFT processing object
	float gScaleFactor = 0.5;			// How much to scale the output, based on window type and overlap
	void process_fft(std::vector<float> const& inBuffer, unsigned int inPointer, std::vector<float>& outBuffer, unsigned int outPointer);
	int gCachedInputBufferPointer = 0;
	
	protected:
	// FFT-related variables
	const int gFftSize = 1024;			// FFT window size in samples
	const int gHopSize = 128;			// How often we calculate a window
	
	// Circular buffer and pointer for assembling a window of samples
	const int gBufferSize = 16384;
	std::vector<float> gInputBuffer;
	int gInputBufferPointer = 0;
	int gHopCounter = 0;
	
	// Circular buffer for collecting the output of the overlap-add process
	std::vector<float> gOutputBuffer;

	// Start the write pointer ahead of the read pointer by at least window + hop, with some margin
	int gOutputBufferWritePointer = gFftSize + 2*gHopSize;
	int gOutputBufferReadPointer = 0;

	// Buffer to hold the windows for FFT analysis and synthesis
	std::vector<float> gAnalysisWindowBuffer;
	std::vector<float> gSynthesisWindowBuffer;
	
	public:
	FFTWrapper();
	float process(float sample);
};