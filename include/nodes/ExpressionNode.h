#ifndef PROLOG_EXPRESSIONNODE_H
#define PROLOG_EXPRESSIONNODE_H

#include <string>
#include <vector>

#include "dictionary/QueryContext.h"
#include "nodes/AbstractNode.h"

namespace prolog {
    class ExpressionNode : public AbstractNode {
    public:
        ExpressionNode(AbstractNode const* initial);
        ~ExpressionNode();
        bool equals(AbstractNode const& n) const override;
        ExpressionNode* add_clause(AbstractNode const* clause);
        QueryContext& resolve(AbstractNode const& query, QueryContext& context) const override;
        std::vector<std::string> get_variable_names() const override;
        std::string to_string() const override;
        std::string debug_string() const override;
    private:
        std::vector<AbstractNode const*> clauses;
    };
}

#endif
