#ifndef PROLOG_FACTNODE_H
#define PROLOG_FACTNODE_H

#include "nodes/AbstractNode.h"

namespace prolog {
    namespace nodes {
        class FactNode : public AbstractNode {
        public:
            FactNode(std::unique_ptr<std::string> lit);
            std::string const& get_literal() const;
            bool matches(FactNode const& n) const;
            bool matches(AbstractNode const& n) const;
        private:
            const std::unique_ptr<std::string> literal;
        };
    }
}

#endif
