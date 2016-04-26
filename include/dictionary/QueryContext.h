#ifndef PROLOG_QUERYCONTEXT_H
#define PROLOG_QUERYCONTEXT_H

#include <vector>
#include <string>
#include <cstdint>

#include "dictionary/Solution.h"

namespace prolog {
    // forward declarations to avoid circular dependencies
    class AbstractNode;
    class VariableNode;
    
    class QueryContext {
    public:
        QueryContext(std::uint32_t initial);
        QueryContext(QueryContext const& source);
        QueryContext& reject();
        QueryContext& reject(std::uint32_t index);
        QueryContext& set_working(std::uint32_t index);
        QueryContext& absorb(QueryContext const& other);
        QueryContext& trim();
        QueryContext& bind(VariableNode const& var, AbstractNode const* binding);
        std::uint32_t solution_count() const;
        std::string to_string() const;
        bool good() const;
    private:
        std::vector<Solution> solutions;
        std::uint32_t working_index;
    };
}

#endif
