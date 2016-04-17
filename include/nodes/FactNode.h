#ifndef PROLOG_FACTNODE_H
#define PROLOG_FACTNODE_H

#include "nodes/AbstractNode.h"

namespace prolog {
    namespace nodes {
        class FactNode : public AbstractNode {
        public:
            FactNode(char const* lit);
            std::string const& get_literal() const;
            bool matches(AbstractNode const& n) override;
            std::string to_string() override;
            
            const types::NodeType type = types::Fact;
        private:
            std::unique_ptr<std::string> literal;
        };
    }
}

#endif
