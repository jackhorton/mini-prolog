#ifndef PROLOG_ARGSNODE_H
#define PROLOG_ARGSNODE_H

#include <list>
#include <string>

#include "nodes/AbstractNode.h"

namespace prolog {
    namespace nodes {
        class ArgumentsNode : public AbstractNode {
        public:
            ArgumentsNode(AbstractNode const* n);
            ~ArgumentsNode();
            ArgumentsNode* push_back(AbstractNode const* n); // push* returns pointers for easier use in bison
            ArgumentsNode* push_front(AbstractNode const* n);
            bool matches(AbstractNode const& n) const override;
            std::string to_string() const override;
        private:
            std::list<AbstractNode const*> args;
        };
    }
}

#endif
