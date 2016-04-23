#ifndef PROLOG_QUERYCONTEXT_H
#define PROLOG_QUERYCONTEXT_H

#include <map>
#include <string>

namespace prolog {
    // forward declarations to avoid circular dependencies
    class AbstractNode;
    class VariableNode;
    
    class QueryContext {
    public:
        QueryContext();
        QueryContext& reject();
        QueryContext& bind(VariableNode const& var, AbstractNode const* binding);
        std::string to_string() const;
        bool good() const;
    private:
        std::map<std::string, AbstractNode const*> bindings;
        bool failed;
    };
}

#endif
