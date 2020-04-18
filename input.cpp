#include "common.h"
#include "output.h"


/*
 * int parse_commandline( int nargs, char** args , map<string, string> &cargs )
 *
 * Arguments:
 * - nargs    Integer number of command line arguments
 * - args     Character pointer array of command line arguments
 * - cargs    Map[command line flag] = command line argument 
 *
 * Parses arguments pased to main() via the command line
 * returns a map of argumets with flags as keys and arguments as values
 *
 */
int parse_commandline( int nargs, char** args,
        std::map<std::string, std::string> &cargs ) {

    for ( int i=0; i<nargs; ++i ) {
        if ( args[i][0] == '-' ) {
            if ( i+1<nargs && args[i+1][0] != '-' ) {
                cargs[args[i]] = args[i+1];       
            } else {
                cargs[args[i]] = "";
            }
        }
    }
    return 0;
} 

/*****************************************************************************/

/*
 * int commandline_logic( :map<string, string> cargs )
 *
 * Arguments:
 * - cargs    Map of command line argumets
 *
 * Goes through command line argumetns, checks for required arguments
 * and optionally prints help
 *
 */
int commandline_logic( std::map<std::string, std::string> &cargs ) {
    
    std::map<std::string, std::string>::iterator it, it1, it2;
    
    // Help flag 
    it = cargs.find("-h");
    if ( it != cargs.end() ) {
        print_help();
        exit( EXIT_SUCCESS );
    }
    it = cargs.find("--help");
    if ( it != cargs.end() ) {
        print_help();
        exit( EXIT_SUCCESS );
    }

    it1 = cargs.find("--input");
    it2 = cargs.find("-i");
    if ( ( it1 == cargs.end() && it2 == cargs.end() ) ||
        ( it1 != cargs.end() && it2 != cargs.end() ) ) {
        std::cout << "ERROR! Use ONE of -i / --input!" << "\n\n";
        print_help();
        exit( EXIT_FAILURE );
    }

    if ( it1 == cargs.end() ) {
        cargs["--input"] = cargs["-i"];
    }

    return 0;
}  

/*****************************************************************************/

/*
 * read_input( map<string, string> cargs, struct input &inp )
 *
 * Arguments:
 * - cargs    Map of command line arguments 
 * - inp      Input struct to hold input parameters
 *
 * Attempts to open and read input file based on the first command line
 * argument passed to the 
 *
 */
int read_input( std::map<std::string, std::string> cargs ) { 
    std::ifstream ifile;
    ifile.open( cargs["--input"], std::fstream::in );
    std::string line, kw;
    do {
        std::getline( ifile, line );
        if ( !( line[0] == '#' || line.length() == 0 ) ) {
            std::istringstream l(line);
            l >> kw;
            if ( kw == "F" ) {
                l >> input.F;
            } else if ( kw == "S" ) {
                l >> input.S;
            } else if ( kw == "bath" ) {
                l >> input.bath;
            } else if ( kw == "eta" ) {
                l >> input.eta;
            } else if ( kw == "kondo" ) {
                l >> input.kondo;
            } else if ( kw == "beta" ) {
                l >> input.beta;
            } else if ( kw == "omegac" ) {
                l >> input.omegac;
            } else if ( kw == "eps" ) {
                l >> input.eps;
            } else if ( kw == "delta" ) {
                l >> input.delta;
            } else if ( kw == "traj" ) {
                l >> input.traj;
            } else if ( kw == "steps" ) {
                l >> input.steps;
            } else if ( kw == "dt" ) {
                l >> input.dt;
            } else if ( kw == "rhoe" ) {
                l >> input.rhoe;
            } else if ( kw == "rhon" ) {
                l >> input.rhon;
            }
        }
    } while ( ifile.good() ); 
    ifile.close();
    return 0;
}

/*****************************************************************************/
