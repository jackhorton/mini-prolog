#ifndef PROLOG_DICTRESPONSE_H
#define PROLOG_DICTRESPONSE_H

#include <vector>

#include "dictionary/QueryContext.h"
#include "nodes/AbstractNode.h"

namespace prolog {
    class DictionaryResponse {
    public:
        DictionaryResponse(AbstractNode const* root, QueryContext context);
        ~DictionaryResponse();
        void prompt() const;
    private:
        AbstractNode const* root; // owned
        QueryContext context;
    };
}

#endif
