#ifndef PROLOG_VARIABLENODE_H
#define PROLOG_VARIABLENODE_H

#include <string>

#include "nodes/AbstractNode.h"
#include "dictionary/QueryContext.h"

namespace prolog {
    class VariableNode : public AbstractNode {
    public:
        VariableNode(char const* name);
        ~VariableNode();
        std::string const& get_literal() const;
        bool equals(AbstractNode const& n) const override;
        QueryContext& resolve(AbstractNode const& n, QueryContext& context) const override;
        std::string to_string() const override;
    private:
        std::string literal;
    };
}

#endif
