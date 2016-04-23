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
        Dictionary& insert(AbstractNode* n);
        DictionaryResponse find(AbstractNode const* query) const;
    private:
        std::vector<AbstractNode*> clauses;
    };
}

#endif
