#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include "nodes/AbstractNode.h"
#include "dictionary/Dictionary.h"
#include "dictionary/DictionaryResponse.h"

using namespace prolog;
using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::move;
using std::vector;

Dictionary& Dictionary::get() {
    static Dictionary instance;
    
    return instance;
}

Dictionary& Dictionary::insert(AbstractNode* n) {
    clauses.push_back(n);
        
    return *this;
}

DictionaryResponse Dictionary::find(AbstractNode const* query) const {
    DictionaryResponse response(query);
    QueryContext* context;
    
    for (auto clause : clauses) {
        context = new QueryContext();
        clause->resolve(*query, *context);
        
        if (context->good()) {
            response.add_solution(context);
        } else {
            delete context;
        }
    }
    
    return response;
}
