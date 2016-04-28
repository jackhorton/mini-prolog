#include <string>

#include "nodes/AbstractNode.h"
#include "dictionary/Dictionary.h"
#include "dictionary/QueryContext.h"

using namespace prolog;
using std::string;

Dictionary& Dictionary::get() {
    static Dictionary instance;
    
    return instance;
}

Dictionary& Dictionary::insert(AbstractNode* n) {
    clauses.push_back(n);
        
    return *this;
}

QueryContext& Dictionary::resolve(AbstractNode const& query, QueryContext& context) const {
    for (AbstractNode const* clause : clauses) {
        QueryContext& ctx = context.create_child();
            
        clause->resolve(query, ctx);
    }
    
    return context;
}

void Dictionary::query(AbstractNode const* query) const {
    QueryContext context;
    
    this->resolve(*query, context);
    
    context.prompt();
    delete query;
}
