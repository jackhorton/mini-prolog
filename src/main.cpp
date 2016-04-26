#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <cstdio>

#include "nodes/all.h"
#include "parser/fix.h"
#include "parser/parser.h"
#include "parser/lexer.h"

using namespace prolog;

int main(int argc, char **argv) {
    // for now, only parse files using clargs
    FILE* input = fopen("tests/family-tree.pl", "r");
    if (input == NULL) {
        fprintf(stderr, "Could not open file\n");
        exit(1);
    }
        
    // set up the initial scanner
    yyscan_t scanner;
    yylex_init(&scanner);
    
    // parse the input file
    yyset_in(input, scanner);
    yyparse(scanner, false);
    
    // parse queries
    std::string query;
    YY_BUFFER_STATE buffer;
    while (std::cin.good()) {
        std::cout << "?- ";
        std::getline(std::cin, query);
        buffer = yy_scan_string(query.c_str(), scanner);
        yyparse(scanner, true);
        yy_delete_buffer(buffer, scanner);
    }
    
    std::cout << "Goodbye!" << std::endl;
    
    // finally, destroy the scanner and files
    yylex_destroy(scanner);
    fclose(input);
}
