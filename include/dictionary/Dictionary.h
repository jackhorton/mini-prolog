#ifndef PROLOG_DICTIONARY_H
#define PROLOG_DICTIONARY_H

#include <vector>

#include "nodes/AbstractNode.h"
#include "dictionary/QueryContext.h"

namespace prolog {
    class Dictionary {
    public:
        static Dictionary& get();
        Dictionary& insert(AbstractNode* n);
        QueryContext& resolve(AbstractNode const& query, QueryContext& context) const;
        void query(AbstractNode const* query) const;
    private:
        std::vector<AbstractNode*> clauses;
    };
}

#endif
