#include "common.h"
#include "fio.h"

struct input_variables input;

int main( int argc, char** args ) {

    // Parse command line argunments
    std::map<std::string, std::string> cargs;
    parse_commandline( argc, args, cargs );
    commandline_logic( cargs );

    // Read input file and parse input arguments
    read_input( cargs );

    // 
    std::cout << "F " << input.F << std::endl;
    std::cout << "S " << input.S << std::endl;

    return 21;
}
