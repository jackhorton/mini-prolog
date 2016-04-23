#include <vector>
#include <iostream>

#include "nodes/AbstractNode.h"
#include "dictionary/QueryContext.h"
#include "dictionary/DictionaryResponse.h"

using namespace prolog;
using std::map;
using std::cerr;
using std::cout;
using std::endl;
using std::cin;

DictionaryResponse::DictionaryResponse(AbstractNode const* root) : root(root) {
    // the dictionaryresponse owns the root node
}

DictionaryResponse::~DictionaryResponse() {
    delete root;
    
    for (QueryContext* context : solutions) {
        delete context;
    }
}

void DictionaryResponse::add_solution(QueryContext* context) {
    // dictionaryresponse owns these contexts
    solutions.push_back(context);
}

void DictionaryResponse::prompt() const {
    uint32_t match_len = solutions.size();
    
    if (match_len == 0) {
        cout << "false." << endl;
        return;
    }
    
    if (match_len > 1) {
        cout << "Found " << match_len << " results. Advancing through results with ';' is not currently supported" << endl;
    }
    
    for (QueryContext* context : solutions) {
        cout << context->to_string() << endl;
    }    
}
