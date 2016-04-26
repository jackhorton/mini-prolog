#ifndef PROLOG_SOLUTION_H
#define PROLOG_SOLUTION_H

#include <map>
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
        std::string to_string() const;
        bool good() const;
    private:
        std::map<std::string, AbstractNode const*> bindings;
        bool failed;
    };
}

#endif
