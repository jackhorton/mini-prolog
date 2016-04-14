#ifndef PROLOG_ABSTRACTNODE_H
#define PROLOG_ABSTRACTNODE_H

namespace prolog {
    namespace nodes {
        class AbstractNode {
        public:
            virtual bool matches(AbstractNode const& n) const = 0;
        };
    }
}

#endif
