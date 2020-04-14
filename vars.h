#pragma once
#include <complex>

// Physical constants
const double pi = 3.141592653589793;
const std::complex<double> eye(0., 1.);

// Global variables
struct input_variables {
    public:
        int F;              // Nuclear DoFs
        int S;              // Electornic DoFs

        double eta;         // Bath coupling parameter
        double kondo;       // Bath Kondo coupling parameter
        double omegac;      // Bath cutoff frequency
        std::string bath;   // Bath type (either 'Ohmic' or 'Debye')
};

struct bath_variables {
    public:
        double * c;         // System-bath coupling coefficients
        double * mass;      // Bath mode masses
        double * omega;     // Bath mode freqencies
};
