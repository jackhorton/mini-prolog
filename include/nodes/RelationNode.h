#ifndef PROLOG_RELATIONNODE_H
#define PROLOG_RELATIONNODE_H

#include <string>
#include <vector>

#include "nodes/AbstractNode.h"
#include "nodes/ArgumentsNode.h"

namespace prolog {
    namespace nodes {
        class RelationNode : public AbstractNode {
        public:
            RelationNode(std::string name, ArgumentsNode const* args);
            ~RelationNode();
            std::string const& get_name() const;
            bool matches(AbstractNode const& n) const override;
            std::string to_string() const override;
        private:
            const std::string name;
            ArgumentsNode const* arguments;
        };
    }
}

#endif
