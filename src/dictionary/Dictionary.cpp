#include <string>
#include <iostream>

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
    
    std::cout << "??????????????????????" << std::endl;
    std::cout << "Resolving query against dictionary:\n" << query.debug_string() << std::endl;
    std::cout << "Current context:\n" << context.debug_string() << std::endl;
    std::cout << "??????????????????????" << std::endl;

    
    for (AbstractNode const* clause : clauses) {
        std::cout << "///////////////////////////////////" << std::endl;
        std::cout << "About to visit node:\n" << clause->debug_string() << std::endl;
        std::cout << "Resulting context before visit:\n" << return_context.debug_string() << std::endl;
        std::cout << "///////////////////////////////////" << std::endl;
        
        for (uint32_t i = 0; i < context.solution_count(); i++) {
            QueryContext ctx(context);
            ctx.set_working(i);
            
            std::cout << "-----------------------------------" << std::endl;
            std::cout << "Current dictionary clause:\n" << clause->debug_string() << std::endl;
            std::cout << "Current query:\n" << query.debug_string() << std::endl;
            std::cout << "Input Solution:\n" << ctx.working().debug_string() << std::endl;
            
            clause->resolve(query, ctx);
            
            QueryContext diff = ctx.diff(context);
            return_context.absorb(diff);
            
            std::cout << "Solution failed? " << !ctx.working().good() << std::endl;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        }
        
        std::cout << "|||||||||||||||||||||||||||||||||||" << std::endl;
        std::cout << "Done visiting node:\n" << clause->debug_string() << std::endl;
        std::cout << "Resulting context after visit:\n" << return_context.debug_string() << std::endl;
        std::cout << "|||||||||||||||||||||||||||||||||||" << std::endl;
    }
    
    context = return_context;
    
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "Done resolving query against dictionary:\n" << query.debug_string() << std::endl;
    std::cout << "Final return context:\n" << return_context.debug_string() << std::endl;
    std::cout << "Set context to:\n" << context.debug_string() << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    
    return context;
}

DictionaryResponse Dictionary::query(AbstractNode const* query) const {
    QueryContext context(1);
    
    context.working().set_external_vars(*query);
    
    this->resolve(*query, context);
    
    return DictionaryResponse(query, context);
}
