//
//  Fir.hpp
//  DSPSysteemAnalyse
//
//  Created by Vincent Van den Broeck on 11/02/2024.
//

#ifndef Fir_hpp
#define Fir_hpp

#include <stdio.h>

class Fir {
protected:
    unsigned int bufferSize;
    double y;
    double * buffer;
public:
    Fir();
    ~Fir();
    virtual double process(double x) = 0;
    void clear();
};

class LowPass : public Fir {
public:
    using Fir::Fir;
    double process(double x) override;
};

class HighPass : public Fir {
public:
    using Fir::Fir;
    double process(double x) override;
};


#endif /* Fir_hpp */
