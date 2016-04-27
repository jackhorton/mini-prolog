#ifndef PROLOG_VARIABLENODE_H
#define PROLOG_VARIABLENODE_H

#include <string>
#include <vector>

#include "nodes/AbstractNode.h"
#include "dictionary/QueryContext.h"

namespace prolog {
    class VariableNode : public AbstractNode {
    public:
        VariableNode(char const* name);
        ~VariableNode();
        std::string const& get_literal() const;
        bool equals(AbstractNode const& n) const override;
        QueryContext& resolve(AbstractNode const& query, QueryContext& context) const override;
        std::vector<std::string> get_variable_names() const override;
        std::string to_string() const override;
        std::string debug_string() const override;
    private:
        std::string literal;
    };
}

#endif
