#include <vector>
#include <forward_list>

#include "parser/NodeVector.h"
#include "nodes/AbstractNode.h"

using namespace prolog;

NodeVector* NodeVector::push(nodes::AbstractNode* node) {
    // why does `NodeVector` use a forward_list, you may ask?
    // well, I the way I set up the parser, arguments get added to the front of the arglist
    // and switching from vector to forward_list was easier
    
    // the benefits of abstraction, right?
    list.push_front(node);
    
    return this;
}

std::vector<nodes::AbstractNode*> NodeVector::get_vector() {
    return std::vector<nodes::AbstractNode*>(list.begin(), list.end());
}
