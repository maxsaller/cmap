#pragma once
#include <complex>
#include <random>
#include <vector>

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
        std::string alg;    // EOM algorithm (either 'vverlet' or 'diag')

        std::string rhoe;   // Initial density matrix of mapping variables
        std::string rhon;   // Initial density matrix of nuclear variables

};

struct bath_variables {
    public:
        std::vector<double> c;      // System-bath coupling coefficients
        std::vector<double> mass;   // Bath mode masses
        std::vector<double> omega;  // Bath mode freqencies

        std::vector<double> xsig;   // Standard deviation for distribution of nuclerar x
        std::vector<double> psig;   // Standard deviation for distribution of nuclerar p
};

struct subsystem_variables {
    public:
        std::vector< std::vector<double> > V;   // Potential energy matrix - constant
};

struct potential {
    public:
        double V0;                                              // State-independent potential
        std::vector< std::vector<double> >  V;                  // Potential energy matrix
        std::vector< double > G0;                               // State-independent fortce
        std::vector< std::vector< std::vector<double> > > G;    // Force tensor
};

struct trajectory_variables {
    public:
        std::vector< double > xn;        // Nuclear position
        std::vector< double > pn;        // Nuclear momentum
        std::vector< double > Xe;        // Mapping variable position
        std::vector< double > Pe;        // Mapping variable momentum
};

struct observables {
    public:
        double si;         // Identity
        double sx;         // Pauli x matrix
        double sy;         // Pauli y matrix
        double sz;         // Pauli x matrix

        double si0;        // Identity time zero
        double sx0;        // Pauli x matrix time zero
        double sy0;        // Pauli y matrix time zero
        double sz0;        // Pauli x matrix time zero

        std::vector< double > pop;
        std::vector< double > pop0;

        // Time
        std::vector< double > time;

        // Pauli correlation functions
        std::vector< double > CII;
        std::vector< double > CIx;
        std::vector< double > CIy;
        std::vector< double > CIz;
        std::vector< double > CxI;
        std::vector< double > Cxx;
        std::vector< double > Cxy;
        std::vector< double > Cxz;
        std::vector< double > CyI;
        std::vector< double > Cyx;
        std::vector< double > Cyy;
        std::vector< double > Cyz;
        std::vector< double > CzI;
        std::vector< double > Czx;
        std::vector< double > Czy;
        std::vector< double > Czz;

        // Population correlation Functions
        std::vector< std::vector< std::vector< double > > > Cpop;
};
