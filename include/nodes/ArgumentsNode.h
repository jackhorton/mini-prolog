#ifndef PROLOG_ARGSNODE_H
#define PROLOG_ARGSNODE_H

#include <list>
#include <vector>
#include <string>

#include "nodes/AbstractNode.h"
#include "dictionary/QueryContext.h"

namespace prolog {
    class ArgumentsNode : public AbstractNode {
    public:
        ArgumentsNode(AbstractNode const* n);
        ~ArgumentsNode();
        ArgumentsNode* push_back(AbstractNode const* n); // push* returns pointers for easier use in bison
        ArgumentsNode* push_front(AbstractNode const* n);
        bool equals(AbstractNode const& n) const override;
        QueryContext& resolve(AbstractNode const& query, QueryContext& context) const override;
        std::vector<std::string> get_variable_names() const override;
        std::string to_string() const override;
        std::string debug_string() const override;
    private:
        std::list<AbstractNode const*> args;
    };
}

#endif
