#include <vector>
#include <memory>
#include <iostream>

#include <cstdlib>

#include "nodes/AbstractNode.h"
#include "dictionary/DictionaryResponse.h"

using namespace prolog;
using std::vector;
using std::shared_ptr;
using std::cerr;
using std::cout;
using std::endl;
using std::cin;

DictionaryResponse::DictionaryResponse(AbstractNode const* root, vector<shared_ptr<AbstractNode>> matches)
  : root(root)
  , matches(matches) {
    // the dictionaryresponse owns the root node
}

DictionaryResponse::~DictionaryResponse() {
    delete root;
}

void DictionaryResponse::prompt() const {
    uint32_t match_len = matches.size();
    char delimeter;
    
    if (match_len == 0) {
        cout << "false." << endl;
        return;
    }
    
    if (match_len > 1) {
        cout << "Found " << match_len << " results. Advancing through results with ';' is not currently supported" << endl;
    }
    
    for (uint32_t i = 0; i < match_len; i++) {
        cout << "true";
        if (i == match_len - 1) {
            cout << ".";
        }
        cout << endl;
    }
}
