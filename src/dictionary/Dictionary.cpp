#include <string>

#include "nodes/AbstractNode.h"
#include "dictionary/Dictionary.h"
#include "dictionary/DictionaryResponse.h"

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
    QueryContext return_context(0);
    
    for (AbstractNode const* clause : clauses) {
        for (uint32_t i = 0; i < context.solution_count(); i++) {
            QueryContext ctx(context);
            ctx.set_working(i);
            
            clause->resolve(query, ctx);
            
            QueryContext diff = ctx.diff(context);
            return_context.absorb(diff);
        }
    }
    
    context = return_context;
    
    return context;
}

DictionaryResponse Dictionary::query(AbstractNode const* query) const {
    QueryContext context(1);
    
    context.working().set_external_vars(*query);
    
    this->resolve(*query, context);
    
    return DictionaryResponse(query, context);
}
