#ifndef PROLOG_DICTIONARY_H
#define PROLOG_DICTIONARY_H

#include <vector>
#include <memory>

#include "nodes/AbstractNode.h"
#include "dictionary/DictionaryResponse.h"

namespace prolog {
    class Dictionary {
    public:
        static Dictionary& get();
        Dictionary& insert(nodes::AbstractNode* n);
        DictionaryResponse find(nodes::AbstractNode const* n) const;
    private:
        std::vector<std::shared_ptr<nodes::AbstractNode>> clauses;
    };
}

#endif
