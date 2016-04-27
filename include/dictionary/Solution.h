#ifndef PROLOG_SOLUTION_H
#define PROLOG_SOLUTION_H

#include <map>
#include <vector>
#include <string>

// dont include VariableNode and AbstractNode if you dont enjoy compiler errors

namespace prolog {
    // forward declarations to avoid circular dependencies
    class AbstractNode;
    class VariableNode;
    
    class Solution {
    public:
        Solution();
        Solution& reject();
        Solution& bind(VariableNode const& var, AbstractNode const* binding);
        Solution& set_external_vars(AbstractNode const& query);
        Solution& alias(std::string source, std::string target);
        std::string to_string() const;
        std::string debug_string() const;
        bool equals(Solution const& other) const;
        bool good() const;
    private:
        std::map<std::string, std::string> aliases;
        std::map<std::string, AbstractNode const*> bindings;
        std::vector<std::string> external_vars;
        bool failed;
    };
}

#endif
