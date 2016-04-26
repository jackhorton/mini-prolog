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

QueryContext& Dictionary::resolve(AbstractNode const& query, QueryContext& context) const {
    QueryContext return_context(0);
    
    for (AbstractNode const* clause : clauses) {
        // get a fresh copy of the incoming context
        QueryContext ctx(context);
        for (uint32_t i = 0; i < ctx.solution_count(); i++) {
            ctx.set_working(i);
            clause->resolve(query, ctx);
        }
        
        // add the solutions that we just found to the "after" state
        return_context.absorb(ctx);
    }
    
    context = return_context.trim();
    
    return context;
}

DictionaryResponse Dictionary::query(AbstractNode const* query) const {
    QueryContext context(1);
    
    this->resolve(*query, context);
    
    return DictionaryResponse(query, context);
}
