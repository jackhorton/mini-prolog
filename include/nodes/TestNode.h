#ifndef PROLOG_TESTNODE_H
#define PROLOG_TESTNODE_H

#include "nodes/AbstractNode.h"

namespace prolog {
    namespace nodes {
        class TestNode : public AbstractNode {
        public:
            TestNode(char const* lit);
            std::string const& get_literal() const;
            virtual bool matches(AbstractNode const& n) override;
            
            const types::NodeType type = types::Test;
        private:
            std::unique_ptr<std::string> literal;
        };
    }
}

#endif
