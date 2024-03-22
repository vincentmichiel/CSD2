//
// Created by Dean on 27/02/2024.
//
#pragma once
#include<iostream>

struct Filter {
    virtual double process(double input) = 0;
    virtual ~Filter(){};
};


//                   IIRFilter
//   X[n] ---->(+)--->[ 1 sample ] ---> Y[n]
//              |                   |
//             (a)<-----------------
//
struct IIRFilter : Filter {
    double process(double input) override {
        // Y[n] = X[n] + aY[n-1]
        feedback = input + (a * feedback);
        return feedback;
    }

    void setCoefficient(double coefficient) {
        // Do not exceed 1, for the safety of all our ears
        a = coefficient;
    }

private:
    double feedback { 0.0 };
    double a { 0.0 }; // Coefficient "a" is mostly used for feedback lines

};


//                    OneZero
//   X[n] ---->(+)--------------------> Y[n]
//              |                  |
//             (b)-->[ 1 sample ]-->
//
struct FIRFilter : Filter {
    double process(double input) override {
        // Y[n] = X[n] - bX[n-1]
        auto output = input - (b * x1);

        x1 = input; // Recaching Delay
        return output;
    }

    void setCoefficient(double coefficient) {
        b = coefficient;
    }

private:
    double x1 {0.0 }; // x1 for a single sample delay
    double b { 0.0 };  // Coefficient "b" is usually used for feed forward lines

};


//                   OnePole
//   X[n] --(b)->(+)--->[ 1 sample ] ---> Y[n]
//              |                   |
//             (a)<-----------------
//
struct OnePole : Filter {
    double process(double input) override {
        // Y[n] = bX[n] + aY[n-1]
        feedback = (b * input) + (a * x1);
        
        x1 = feedback;
        return feedback;
    }

    void setCoefficient(double coefficient) {
        a = coefficient;
        b = 1.0f - a;
    }

private:
    double feedback { 0.0 } ;
    double a { 0.0 };
    double b { 0.0 };
    double x1 { 0.0 };
};


//                   4_Pole / Simple Cascade
//   X[n]--->[OnePole][OnePole][OnePole][OnePole]--->Y[n]
//
struct SimpleLadder : Filter {
    double process(double input) override {
        double output = input;
        for(int i = 0; i < 4; i++){
            output = filters[i].process(output);
        }
        
        return output;
    }

    void setCoefficient(double coefficient) {
        for(int i = 0; i < 4; i++){
            filters[i].setCoefficient(coefficient);
        }
    }

private:    
    OnePole filters[4];
};


//                   4 Sample
//   X[n] --(b)->(+)--->[ 4 sample ] ---> Y[n]
//              |                   |
//             (a)<-----------------
//
struct FourSample : Filter {
    double process(double input) override {
        // Y[n] = bX[n] + aY[n-4]
        feedback = (b * input) + (a * buffer[3]);
        
        // update buffer
        for(int i = 1; i < 4; i++){
            buffer[i] = buffer[i - 1];
        }
        buffer[0] = feedback;
        
        return feedback;
    }

    void setCoefficient(double coefficient) {
        a = coefficient;
        b = 1.0f - a;
    }


private:
    double buffer[4] = {0, 0, 0, 0};
    double feedback { 0.0 };
    double b { 0.0 };
    double a { 0.0 };
};


//                   Halve Biquad
//   X[n] --(b)->(+)--------------------> Y[n]
//                |                  |
//               (a1)<----------[ 1 sample ]
//                |                  |
//               (a2)<----------[ 1 sample ]
//
//
struct HalfBiquad : Filter {
    double process(double input) override {
      // y[n] = bX[n] - a1Y[n-1] - a2Y[n-2]
        feedback = (b * input) - (a1 * y1) - (a2 * y2);
        y2 = y1;
        y1 = feedback;
        
        return feedback;
    }

    void setBCoefficient(double coefficient){
        b = coefficient;
    }

    void setA1Coefficient(double coefficient) {
        a1 = coefficient;
    }

    void setA2Coefficient(double coefficient) {
        a2 = coefficient;
    }


private:
    double feedback {0.0};
    double y1 {0.0};
    double y2 {0.0};
    double b {0.0};
    double a1 {0.0};
    double a2 {0.0};
};


struct Biquad : Filter {
public:
    double process(double input) override {
        // y[n] = b0X[n] + b1X[n-1] + b2X[n-2] - a1Y[n-1] - a2Y[n-2]
        feedback = (b0 * input) + (b1 * x1) + (b2 * x2) - (a0 * y1) - (a1 * y2);
        
        x2 = x1;
        x1 = input;
        y2 = y1;
        y1 = feedback;
        
        return feedback;
    }
    
    void setCoefficients(double b0, double b1, double b2, double a0, double a1){
        this->b0 = b0;
        this->b1 = b1;
        this->b2 = b2;
        this->a0 = a0;
        this->a1 = a1;
    }
    
    void clear(){
        x1 = 0;
        x2 = 0;
        y1 = 0;
        y2 = 0;
    }
   

private:
    double feedback {0.0};
    double b0 {0.0};
    double b1 {0.0};
    double b2 {0.0};
    double a0 {0.0};
    double a1 {0.0};
    double x1 {0.0};
    double x2 {0.0};
    double y1 {0.0};
    double y2 {0.0};
};
