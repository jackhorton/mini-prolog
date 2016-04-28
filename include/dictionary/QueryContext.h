#ifndef PROLOG_QUERYCONTEXT_H
#define PROLOG_QUERYCONTEXT_H

#include <vector>
#include <map>
#include <utility>
#include <string>

namespace prolog {
    // forward declarations to avoid circular dependencies
    class AbstractNode;
    class VariableNode;
    
    class QueryContext {
    public:
        QueryContext();
        QueryContext(QueryContext const* parent);
        ~QueryContext();
        QueryContext& reject();
        QueryContext& alias(std::string source, std::string target);
        QueryContext& bind(VariableNode const& var, AbstractNode const* binding);
        std::pair<std::string, AbstractNode const*> find(VariableNode const& var) const;
        QueryContext& create_child();
        std::string to_string() const;
        std::string debug_string() const;
        void prompt() const;
        bool good() const;
    private:
        std::string const& resolve_variable_name(std::string const& original_name) const;
        bool status;
        std::vector<QueryContext*> children;
        std::map<std::string, AbstractNode const*> bindings;
        std::map<std::string, std::string> aliases;
        QueryContext const* parent;
    };
}

#endif
