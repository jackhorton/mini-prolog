#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

#include "nodes/all.h"
#include "parser/fix.h"
#include "parser/parser.h"
#include "parser/lexer.h"

using namespace prolog;

int main(int argc, char **argv) {
    // set up the initial scanner
    yyscan_t scanner;
    yylex_init(&scanner);
    
    // parse the input file
    yyset_in(stdin, scanner);
    yyparse(scanner);
    
    // finally, destroy the scanner and files
    yylex_destroy(scanner);
    std::cout << "Goodbye!" << std::endl;
}
