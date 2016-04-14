#include <iostream>

#include <cstdlib>
#include <cstdio>

#include "main.h"
#include "nodes/FactNode.h"
#include "dictionary.h"
// #include "parser.h"

// int yyparse();

using namespace prolog;

int main(int argc, char **argv) {
    // yyparse();
    
    nodes::AbstractNode *n1 = new nodes::FactNode(std::unique_ptr<std::string>(new std::string("node1")));
    nodes::AbstractNode *n2 = new nodes::FactNode(std::unique_ptr<std::string>(new std::string("node2")));
    
    std::cout << n1->matches(*n2) << std::endl;
}
