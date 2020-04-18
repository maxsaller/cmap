#include "common.h"
#include "input.h"
#include "output.h"
#include "observables.h"
#include "spin_boson.h"
#include "spectral_density.h"

struct subsystem_variables subsystem;
struct trajectory_variables traj;
struct input_variables input;
struct bath_variables bath;
struct observables obs;
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
    traj.xn.resize(input.F);
    traj.pn.resize(input.F);
    traj.Xe.resize(input.S);
    traj.Pe.resize(input.S);
    observables_init();

    /* =========================== TRAJECTORIES ============================ */
    std::cout << "\nTRAJECTORIES\n";
    for ( int t=1; t<=input.traj; ++t ) {

        // Sample initial conditions
        sample_bath();
        sample_subsystem();

        // Compute time-zero operators and observables
        time_zero_ops();
        std::cout << "Trajectoy: " << t
                  << "\n- sig_0 (0) = " << obs.si0
                  << "\n- sig_x (0) = " << obs.sx0
                  << "\n- sig_y (0) = " << obs.sy0
                  << "\n- sig_z (0) = " << obs.sz0 << "\n\n";
        observables( 0 );

        // Propagate trajectories
        for ( int ts=1; ts<=input.steps; ++ts ) {

            // Propagate for a single timesteps

            // Compute time-t operators
            time_t_ops();

            // Compute observables
            observables( ts );


        }

    }


    /* ======================== AVERAGING & OUTPUT ========================= */

    // Average observable arrays
    average();

    // Output observables
    write_observables();

    return 21;
}
