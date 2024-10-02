#include <Bela.h>
#include <libraries/Fft/Fft.h>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>

class FFTEffect {
	public:
	FFTEffect();
	virtual ~FFTEffect();
	
	// multithreading variables
	static void process_fft_background_static(void *arg);
	float process(float in);
	
	protected:
	// FFT-related variables
	Fft gFft;							// FFT processing object
	const int gFftSize = 1024;			// FFT window size in samples
	virtual void processSpectrum();
	
	private:
	// FFT-related variables
	const int gHopSize = 128;			// How often we calculate a window
	float gScaleFactor = 0.5;			// How much to scale the output, based on window type and overlap
	
	// multithreading variables
	void process_fft_background();
	AuxiliaryTask gFftTask;
	int gCachedInputBufferPointer = 0;

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
	
	void process_fft(std::vector<float> const& inBuffer, unsigned int inPointer, std::vector<float>& outBuffer, unsigned int outPointer);
};