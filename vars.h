#pragma once
#include <complex>
#include <random>

// Physical constants
const double pi = 3.141592653589793;
const std::complex<double> eye(0., 1.);

// Global variable structs
struct input_variables {
    public:
        int F;              // Nuclear DoFs
        int S;              // Electornic DoFs

        double eps;         // Spin boson energy bias
        double delta;       // Spin boson coupling
        double eta;         // Bath coupling parameter
        double kondo;       // Bath Kondo coupling parameter
        double beta;        // Inverse temperature
        double omegac;      // Bath cutoff frequency
        std::string bath;   // Bath type (either 'Ohmic' or 'Debye')

        int traj;           // Number of trajectories
        int steps;          // Number of timesteps per trajectory
        double dt;          // Duration of timestep

        std::string rhoe;   // Initial density matrix of mapping variables
        std::string rhon;   // Initial density matrix of nuclear variables

};

struct bath_variables {
    public:
        double * c;         // System-bath coupling coefficients
        double * mass;      // Bath mode masses
        double * omega;     // Bath mode freqencies

        double * xsig;      // Standard deviation for distribution of nuclerar x
        double * psig;      // Standard deviation for distribution of nuclerar p
};

struct subsystem_variables {
    public:
        double ** V;        // Potential energy matrix - constant
};

struct potential {
    public:
        double     V0;
        double **  V;
        double *   F0;
        double *** F;
};

struct trajectory_variables {
    public:
        double *  xn;
        double *  pn;
        double ** Xe;
        double ** Pe;
};
