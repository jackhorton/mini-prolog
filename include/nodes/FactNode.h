#ifndef PROLOG_FACTNODE_H
#define PROLOG_FACTNODE_H

#include "nodes/AbstractNode.h"

namespace prolog {
    namespace nodes {
        class FactNode : public AbstractNode {
        public:
            FactNode(char const* lit);
            ~FactNode();
            std::string const& get_literal() const;
            bool matches(AbstractNode const& n) const override;
            std::string to_string() const override;
        private:
            std::string literal;
        };
    }
}

#endif
