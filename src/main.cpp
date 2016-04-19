#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <cstdio>

#include "nodes/FactNode.h"
#include "nodes/RelationNode.h"
#include "Dictionary.h"
#include "parser/NodeVector.h" // this needs to be here because what is proper linking
#include "parser/fix.h"
#include "parser/parser.h"
#include "parser/lexer.h"

using namespace prolog;

int main(int argc, char **argv) {
    // for now, only parse files using clargs
    FILE* input = fopen("tests/facts-and-relations.pl", "r");
    if (input == NULL) {
        fprintf(stderr, "Could not open file\n");
        exit(1);
    }
    
    FILE* queries = fdopen(0, "r");
    if (queries == NULL) {
        fprintf(stderr, "Could not open stdin\n");
        exit(1);
    }
    
    // set up the initial scanner
    yyscan_t scanner;
    yylex_init(&scanner);
    
    // parse the input file
    yyset_in(input, scanner);
    yyparse(scanner);
    
    // parse queries
    // yyset_in(queries, scanner);
    // yyparse(scanner);
    
    // finally, destroy the scanner and files
    yylex_destroy(scanner);
    fclose(input);
    // fclose(queries);
    
    nodes::FactNode* n1 = new nodes::FactNode("mary");
    nodes::FactNode* n2 = new nodes::FactNode("joe");
    nodes::FactNode n3("apple");
    std::vector<nodes::AbstractNode*> args {n1, n2};
    nodes::RelationNode relation("likes", args);
    auto results = Dictionary::get().find(relation);
    if (results.size() > 0) {
        std::cout << results[0]->to_string() << std::endl;
    } else {
        std::cout << "No matches found" << std::endl;
    }
    
    results = Dictionary::get().find(n3);
    if (results.size() > 0) {
        std::cout << results[0]->to_string() << std::endl;
    } else {
        std::cout << "No matches found" << std::endl;
    }
}
