#include "common.h"
#include "fio.h"
#include "sden.h"

void print_header();

struct input_variables input;
struct bath_variables bath;

int main( int argc, char** args ) {

    print_header();

    /* === INPUT PARSING === */
    // Parse command line argunments
    std::map<std::string, std::string> cargs;
    parse_commandline( argc, args, cargs );
    commandline_logic( cargs );

    // Read input file and parse input arguments
    read_input( cargs );

    /* === INITIALISATION === */
    std::cout << "Intitialisation\n";

    // Initialise harmonic bath
    bath_init();

    return 21;
}

void print_header(){
    std::cout   << "========================================\n"
                << "                  CMAP                  \n"
                << "             Version: 0.1.3             \n"
                << " Copyright 2020 Maximilian A. C. Saller \n"
                << "========================================\n\n";
}
