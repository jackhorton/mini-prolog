#include <iostream>
#include <string>
#include <memory>

#include <cstdlib>
#include <cstdio>

#include "main.h"
#include "nodes/FactNode.h"
#include "nodes/TestNode.h"
#include "Dictionary.h"
#include "parser.h"
#include "lexer.h"

// int yyparse();

using namespace prolog;

int main(int argc, char **argv) {
    // for now, only parse files using clargs
    FILE* input = fopen("tests/basic-facts.pl", "r");
    if (input == NULL) {
        fprintf(stderr, "Could not open file\n");
        exit(1);
    }
        
    yyscan_t scanner;
    yylex_init(&scanner);
    yyset_in(input, scanner);
    
    yyparse(scanner);
    
    yylex_destroy(scanner);
    
    nodes::FactNode n1("apple");
    auto results = Dictionary::get().find(n1);
    std::cout << (*results)[0]->to_string() << std::endl;
        
    // nodes::AbstractNode *n1 = new nodes::FactNode("node1");
    // nodes::AbstractNode *n2 = new nodes::TestNode("node2");
    // nodes::AbstractNode *n3 = new nodes::TestNode("node2");

    // std::cout << n1->matches(*n2) << std::endl;
    // std::cout << n2->matches(*n3) << std::endl;
}
