#ifndef PROLOG_RELATIONNODE_H
#define PROLOG_RELATIONNODE_H

#include <string>
#include <vector>

#include "nodes/AbstractNode.h"

namespace prolog {
    namespace nodes {
        class RelationNode : public AbstractNode {
        public:
            RelationNode(std::string name, std::vector<AbstractNode*> args);
            ~RelationNode();
            std::string const& get_name() const;
            bool matches(AbstractNode const& n) override;
            std::string to_string() const override;
        private:
            const std::string name;
            const std::vector<AbstractNode*> arguments;
        };
    }
}

#endif
