#include "common.h"

void subsystem_init() {

    // Allocate Spin-Boson constant energy matrix
    subsystem.V.resize(input.S);
    for ( int i=0; i<input.S; ++i ) {
        subsystem.V[i].resize(input.S);
    }
    
    // Energies
    subsystem.V[0][0] = input.eps;
    subsystem.V[1][1] = -input.eps;

    // Couplings
    subsystem.V[0][1] = input.delta;
    subsystem.V[1][0] = input.delta;

    std::cout << "\n- Initialising subsystem potentital energy matrix\n";
    std::cout   << std::fixed << std::setprecision(4)
                << std::setw(8) << subsystem.V[0][0]
                << std::setw(8) << subsystem.V[0][1] << std::endl
                << std::setw(8) << subsystem.V[1][0] 
                << std::setw(8) << subsystem.V[1][1] << std::endl;

    // Allocate potential and force matrices
    pot.V.resize(input.S);
    for ( int i=0; i<input.S; ++i ) {
        pot.V[i].resize(input.S);
    }
    pot.G0.resize(input.F);
    pot.G.resize(input.F);
    for ( int i=0; i<input.F; ++i ) {
        pot.G[i].resize(input.S);
        for ( int j=0; j<input.S; ++j ) {
            pot.G[i][j].resize(input.S);
        }
    }

    // Initialize standard deviations for nuclear distributions
    bath.xsig.resize( input.F );
    bath.psig.resize( input.F );
    for ( int i=0; i<input.F; ++i ) {
        bath.xsig[i] = std::sqrt( 1 / ( 2. * bath.mass[i] * bath.omega[i] * \
         std::tanh( input.beta * bath.omega[i] / 2. ) ) );
        bath.psig[i] = std::sqrt( bath.mass[i] * bath.omega[i] / \
            ( 2. * std::tanh( input.beta * bath.omega[i] / 2. ) ) );
    }
}

void sample_bath() {
    
    // Wigner transform of uncoupled, thermal equilibtrium bath
    if ( input.rhon.compare( "thermal" ) == 0 ) {
        for ( int i=0; i<input.F; ++i ) {
            std::normal_distribution<double> xdist(0., bath.xsig[i]);
            std::normal_distribution<double> pdist(0., bath.psig[i]);

            traj.xn[i] = xdist(rgen);
            traj.pn[i] = pdist(rgen);
        }
    } else {
        std::cout   << "ERROR: Options for input argument are:\n"
                    << "       rhon = ['thermal']\n";
        exit( EXIT_FAILURE );

    }
}

void sample_subsystem() {

    // Sampling from phi or phi squared
    double sig;
    if ( input.rhoe.compare( "phi" ) == 0 ) {
        sig = std::sqrt(1./ 2.);
    } else if ( input.rhoe.compare( "phi2" ) == 0 ) {
        sig = 1./ 2.;
    } else {
        std::cout   << "ERROR: Options for input argument are:\n"
                    << "       rhoe = ['phi', 'phi2']\n";
        exit( EXIT_FAILURE );
    }

    std::normal_distribution<double> dist(0., sig );

    for ( int i=0; i<input.S; ++i ) {
        traj.Xe[i] = dist(rgen);
        traj.Pe[i] = dist(rgen);
    }
}

void sb_pot() {

    // State independent potential and force
    pot.V0 = 0;
    for ( int i=0; i<input.F; ++i ) {
        pot.V0 += 0.5 * bath.mass[i] * bath.omega[i]*bath.omega[i] * traj.xn[i]*traj.xn[i];
        pot.G0[i] = bath.mass[i] * bath.omega[i]*bath.omega[i] * traj.xn[i];
    }

    // Potential and force matrices
    for ( int i=0; i<input.S; ++i ){
        for ( int j=0; j<input.S; ++j ){
            pot.V[i][j] = subsystem.V[i][j];
            for ( int k=0; k<input.F; ++k ){
                pot.V[i][j] += bath.c[k] * traj.xn[k];
                pot.G[k][i][j] = 0.;
                pot.G[k][i][i] = bath.c[k];
            }
        }
    }

    // Shift trace from matrices to state independent potential and force
    double trace = ( pot.V[0][0] + pot.V[1][1] ) / 2.;
    pot.V[0][0] -= trace;
    pot.V[1][1] -= trace;
    pot.V0 += trace;

    double ftrace [input.F];
    for ( int i=0; i<input.F; ++i ){
        ftrace[i] = ( pot.G[i][0][0] + pot.G[i][1][1] ) / 2.;
        pot.G[i][0][0] -= ftrace[i];
        pot.G[i][1][1] -= ftrace[i];
        pot.G0[i] += ftrace[i];
    }

}
