#ifndef PROLOG_RULENODE_H
#define PROLOG_RULENODE_H

#include <string>

#include "dictionary/QueryContext.h"
#include "nodes/AbstractNode.h"

namespace prolog {
    
    class RuleNode : public AbstractNode {
    public:
        RuleNode(AbstractNode const* head, AbstractNode const* body);
        ~RuleNode();
        bool equals(AbstractNode const& n) const override;
        QueryContext& resolve(AbstractNode const& n, QueryContext& context) const override;
        std::string to_string() const override;
        std::string debug_string() const override;
    private:
        AbstractNode const* head;
        AbstractNode const* body;
    };
}

#endif
