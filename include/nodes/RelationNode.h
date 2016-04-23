#ifndef PROLOG_RELATIONNODE_H
#define PROLOG_RELATIONNODE_H

#include <string>
#include <vector>

#include "nodes/AbstractNode.h"
#include "nodes/ArgumentsNode.h"
#include "dictionary/QueryContext.h"

namespace prolog {
    namespace nodes {
        class RelationNode : public AbstractNode {
        public:
            RelationNode(std::string name, ArgumentsNode const* args);
            ~RelationNode();
            std::string const& get_name() const;
            bool equals(AbstractNode const& n) const override;
            QueryContext& resolve(AbstractNode const& n, QueryContext& context) const override;
            std::string to_string() const override;
        private:
            std::string const name;
            ArgumentsNode const* arguments;
        };
    }
}

#endif
