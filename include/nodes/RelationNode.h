#ifndef PROLOG_RELATIONNODE_H
#define PROLOG_RELATIONNODE_H

#include <string>
#include <vector>

#include "nodes/AbstractNode.h"
#include "nodes/ArgumentsNode.h"
#include "dictionary/QueryContext.h"

namespace prolog {
    class RelationNode : public AbstractNode {
    public:
        RelationNode(std::string name, ArgumentsNode const* args);
        ~RelationNode();
        std::string const& get_name() const;
        bool equals(AbstractNode const& n) const override;
        QueryContext& resolve(AbstractNode const& query, QueryContext& context) const override;
        std::vector<std::string> get_variable_names() const override;
        std::string to_string() const override;
        std::string debug_string() const override;
    private:
        std::string const name;
        ArgumentsNode const* arguments;
    };
}

#endif
