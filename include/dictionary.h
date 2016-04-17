#ifndef PROLOG_DICTIONARY_H
#define PROLOG_DICTIONARY_H

#include <vector>

#include "nodes/AbstractNode.h"

namespace prolog {
    class Dictionary {
    public:
        static Dictionary& get();
        Dictionary& insert(nodes::AbstractNode* n);
        std::vector<std::shared_ptr<nodes::AbstractNode>> find(nodes::AbstractNode& n) const;
    private:
        std::vector<std::shared_ptr<nodes::AbstractNode>> clauses;
    };
}

#endif
