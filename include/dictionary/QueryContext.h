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
        std::pair<std::string, AbstractNode const*> find(std::string const& variable_name) const;
        QueryContext& create_child();
        QueryContext& collapse_children();
        std::string to_string() const;
        std::string debug_string() const;
        void set_external_vars(AbstractNode const& query);
        void prompt() const;
        bool equals(QueryContext const& other) const;
        bool good() const;
    private:
        std::string const& resolve_variable_name(std::string const& original_name) const;
        std::string to_root_string() const;
        std::string to_child_string(std::vector<std::string> const& important_vars) const;
        bool status;
        std::vector<QueryContext*> children;
        std::map<std::string, AbstractNode const*> bindings;
        std::map<std::string, std::string> aliases;
        std::vector<std::string> external_vars;
        QueryContext const* parent;
    };
}

#endif
