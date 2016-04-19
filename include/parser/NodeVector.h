// Apparently Bison can not and will not allow "non-POD (Plain Old Data)" objects in unions.
// This barbaric restriction means no std::vectors (or unique_ptrs or just about anything useful, fwiw)
// As such, the astute programmer I am, I am now implementing my own container class to fight the barbarism
// May my fortune against the barbarism be better than the Romans'

#ifndef PROLOG_BISONFIX_NODEVECTOR_H
#define PROLOG_BISONFIX_NODEVECTOR_H

#include <vector>
#include <forward_list>

#include "nodes/AbstractNode.h"

namespace prolog {
    class NodeVector {
    public:
        NodeVector* push(nodes::AbstractNode* node);
        std::vector<nodes::AbstractNode*> get_vector();
    private:
        std::forward_list<nodes::AbstractNode*> list;
    };
}


#endif
