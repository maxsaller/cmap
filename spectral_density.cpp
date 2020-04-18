#include "common.h"

void init_ohmic_bath();
void init_debye_bath();

void bath_init() {
    
    // Allocate memory for bath variables
    bath.c = new double [input.F];
    bath.omega = new double [input.F];
    bath.mass = new double [input.F];

    // Bath mode masses
    for ( int i=0; i < input.F; ++i ) {
        bath.mass[i] = 1.0;
    }

    // Parse bath coupling strength/Kondo parameter
    if ( ( input.eta != 0 ) && ( input.kondo != 0 ) ) {
        if ( input.kondo != 2 * input.eta / pi ) {
            std::cout << "ERROR! Bath parameter inconsistency:\n";
            std::cout << "       It is recommended to give either eta or kondo!\n";
            std::cout << "       If both are give, kondo must equal 2*eta/pi!\n";
            exit( EXIT_FAILURE );
        }
    } else if ( ( input.eta == 0 ) && ( input.kondo != 0 ) ) {
        input.eta = pi * input.kondo / 2;
    } else if ( ( input.kondo == 0 ) && ( input.eta != 0 ) ) {
        input.kondo = 2 * input.eta / 2;
    } else {
        std::cout << "ERROR! Bath parameters incomplete:\n";
        std::cout << "       Either eta or kondo must be given!\n";
        exit( EXIT_FAILURE );
    }

    // Set spectral density type and call corresponding init function
    if ( input.bath.compare("ohmic") == 0 ) {
        init_ohmic_bath();
    } else if ( input.bath.compare("debye") == 0 ) {
        init_debye_bath();
    } else {
        std::cout << "ERROR! Options for input argument are:\n";
        std::cout << "       bath = ['ohmic', 'debye']\n";
        exit( EXIT_FAILURE );
    }

}

void init_ohmic_bath() {
    std::cout   << "- Sampling "
                << input.F
                << " mode hamonic bath with Ohmic spectral density\n";
    
    // Discretize spectral density as per JCP 122, 084106 (2005)
    #pragma omp parallel for
    for ( int i=0; i<input.F; ++i ) {
        bath.omega[input.F-1-i] = -input.omegac * std::log( (i+0.5)/input.F );
    }

    // Calculate density of each frequency, spectral density and coefficients
    double density [input.F];
    double J [input.F];
    #pragma omp parallel for
    for ( int i=0; i<input.F; ++i ) {
        density[i] = input.F / input.omegac * std::exp( -bath.omega[i]/input.omegac );
        J[i] = input.eta * bath.omega[i] * std::exp( - bath.omega[i]/input.omegac );
        bath.c[i] = std::sqrt( 2 / pi * bath.mass[i] * bath.omega[i] * J[i] / density[i]);
    }

    std::cout   << "  Maximum frequency: "
                << bath.omega[input.F-1]
                << " au"
                << std::endl;
}

void init_debye_bath() {
    std::cout   << "- Sampling "
                << input.F
                << " mode hamonic bath with Debye spectral density\n";

    // Discretize spectral density as per JCP 122, 084106 (2005)
    #pragma omp parallel for
    for ( int i=0; i<input.F; ++i ) {
        bath.omega[i] = input.omegac * std::tan( pi / 2. * (i+1)/(float)(input.F+1) );
    }

    // Calculate density of each frequency, spectral density and coefficients
    //self.eta * self.omegac * omega / (omega**2 + self.omegac**2)
    double density [input.F];
    double J [input.F];
    #pragma omp parallel for
    for ( int i=0; i<input.F; ++i ) {
        density[i] = 2. * (input.F+1)/pi * input.omegac;
        density[i] = density[i] / (bath.omega[i]*bath.omega[i] + input.omegac*input.omegac);
        J[i] = input.eta * input.omegac * bath.omega[i];
        J[i] = J[i] / (bath.omega[i]*bath.omega[i] + input.omegac*input.omegac);
        bath.c[i] = std::sqrt( 2 / pi * bath.mass[i] * bath.omega[i] * J[i] / density[i]);
    }

    std::cout   << "  Maximum frequency: "
                << bath.omega[input.F-1]
                << " au"
                << std::endl;
}
