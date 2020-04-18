#include "common.h"
#include "input.h"
#include "output.h"
#include "spin_boson.h"
#include "spectral_density.h"


struct subsystem_variables subsystem;
struct trajectory_variables traj;
struct input_variables input;
struct bath_variables bath;
struct potential pot;

// Start random number generator
std::ranlux48 rgen;

int main( int argc, char** args ) {

    print_header();


    /* =========================== INPUT PARSING =========================== */
    // Parse command line argunments
    std::map<std::string, std::string> cargs;
    parse_commandline( argc, args, cargs );
    commandline_logic( cargs );

    // Read input file and parse input arguments
    read_input( cargs );


    /* =========================== INITIALIZATION ========================== */
    std::cout << "INITIALIZATION\n";

    // Initialise harmonic bath
    bath_init();

    // Initialise subsystem and potential energy matrix
    subsystem_init();

    // Initialise trajectory  arrays
    traj.xn = new double [input.F];
    traj.pn = new double [input.F];
    traj.Xe = new double * [input.F];
    traj.Pe = new double * [input.F];
    for ( int i=0; i<input.F; ++i ) {
        traj.Xe[i] = new double [input.S];
        traj.Pe[i] = new double [input.S];
    }


    /* =========================== TRAJECTORIES ============================ */
    std::cout << "\nTRAJECTORIES\n";
    for ( int t=1; t<=input.traj; ++t ) {

        // Sample initial conditions
        sample_bath();
        sample_subsystem();

        // Compute time-zero operators

        // Propagate trajectories
        for ( int ts=1; ts<=input.steps; ++ts ) {

            // Propagate for a single timesteps

            // Compute time-t operators

        }

    }


    /* ======================== AVERAGING & OUTPUT ========================= */

    return 21;
}

