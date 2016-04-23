#ifndef PROLOG_QUERYCONTEXT_H
#define PROLOG_QUERYCONTEXT_H

#include <map>
#include <string>

namespace prolog {
    // forward declarations to avoid circular dependencies
    namespace nodes {
        class AbstractNode;
        class VariableNode;
    }
    
    class QueryContext {
    public:
        QueryContext();
        QueryContext& reject();
        QueryContext& bind(nodes::VariableNode const& var, nodes::AbstractNode const* binding);
        bool good() const;
    private:
        std::map<std::string, nodes::AbstractNode const*> bindings;
        bool failed;
    };
}

#endif
