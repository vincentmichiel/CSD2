class Effect {
	public: 
	Effect(float mix = 1.0);
	virtual ~Effect();
	
	// setters
	void setMix(float mix);
	void setBypass(bool bypass);
	
	// methods
	float process(float sample = 0.0f, int channel = -1);
	
	private:
	bool bypass;
	float mix;
	
	virtual float applyEffect(float sample);
    virtual float applyEffect(float sample, int channel);
};