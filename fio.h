#include "common.h"

int parse_commandline( int, char**, std::map<std::string, std::string>& );
int commandline_logic( std::map<std::string, std::string> cargs );
int read_input( std::map<std::string, std::string>, struct input& );
