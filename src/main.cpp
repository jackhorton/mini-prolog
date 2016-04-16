#include <iostream>
#include <string>
#include <memory>

#include <cstdlib>
#include <cstdio>

#include "main.h"
#include "nodes/FactNode.h"
#include "nodes/TestNode.h"
#include "Dictionary.h"
// #include "parser.h"

// int yyparse();

using namespace prolog;

int main(int argc, char **argv) {
    // yyparse();
    
    nodes::AbstractNode *n1 = new nodes::FactNode("node1");
    nodes::AbstractNode *n2 = new nodes::TestNode("node2");
    nodes::AbstractNode *n3 = new nodes::TestNode("node2");

    std::cout << n1->matches(*n2) << std::endl;
    std::cout << n2->matches(*n3) << std::endl;
}
