#ifndef PROLOG_DICTIONARY_H
#define PROLOG_DICTIONARY_H

#include <vector>

#include "nodes/AbstractNode.h"

namespace prolog {
    class Dictionary {
    public:
        static Dictionary& get();
        Dictionary& insert(nodes::AbstractNode const& n);
        std::vector<nodes::AbstractNode const*> const* find(nodes::AbstractNode const& n) const;
    private:
        Dictionary();
        std::vector<nodes::AbstractNode const*> clauses;
    };
}

#endif
