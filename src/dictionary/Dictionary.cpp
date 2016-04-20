#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include "nodes/AbstractNode.h"
#include "dictionary/Dictionary.h"
#include "dictionary/DictionaryResponse.h"

using namespace prolog;
using namespace prolog::nodes;
using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::move;
using std::vector;

Dictionary& Dictionary::get() {
    static Dictionary instance;
    
    return instance;
}

Dictionary& Dictionary::insert(nodes::AbstractNode* n) {
    clauses.push_back(shared_ptr<AbstractNode>(n));
        
    return *this;
}

DictionaryResponse Dictionary::find(AbstractNode const* n) const {
    vector<shared_ptr<AbstractNode>> matches;
    
    for (auto clause : clauses) {
        if (n->matches(*clause)) {
            matches.push_back(clause);
        }
    }
    
    return DictionaryResponse(n, matches);
}
