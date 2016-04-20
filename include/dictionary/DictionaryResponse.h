#ifndef PROLOG_DICTRESPONSE_H
#define PROLOG_DICTRESPONSE_H

#include <vector>
#include <memory>

#include "nodes/AbstractNode.h"

namespace prolog {
    class DictionaryResponse {
    public:
        DictionaryResponse(nodes::AbstractNode const* root, std::vector<std::shared_ptr<nodes::AbstractNode>> const matches);
        ~DictionaryResponse();
        void prompt() const;
    private:
        nodes::AbstractNode const* root; // owned
        std::vector<std::shared_ptr<nodes::AbstractNode>> const matches;
    };
}

#endif
