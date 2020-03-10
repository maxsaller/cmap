#include "common.h"
#include "fio.h"

int main( int argc, char** args ) {

    std::map<std::string, std::string> cargs;
    parse_commandline( argc, args, cargs );

    commandline_logic( cargs );

    struct input iargs;
    read_input( cargs, iargs );
    
    std::cout << "F " << iargs.F << std::endl;
    std::cout << "S " << iargs.S << std::endl;

    return 21;
}
