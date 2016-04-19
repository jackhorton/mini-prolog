#include <string>
#include <memory>
#include <iostream>

#include "nodes/FactNode.h"

using namespace prolog::nodes;
using std::unique_ptr;
using std::move;
using std::string;

FactNode::FactNode(char const* lit) : AbstractNode(types::Fact), literal(string(lit)) {}

FactNode::~FactNode() {}

string const& FactNode::get_literal() const {
    return literal;
} 

bool FactNode::matches(AbstractNode const& n) {
    std::cout << "trying to match factnode " << literal << " against ";
    if (n.type == types::Fact) {
        FactNode const* fact = static_cast<FactNode const*>(&n);
        std::cout << fact->literal << std::endl;
        return (literal.compare(fact->literal) == 0);
    } else {
        std::cout << "another abstractnode" << std::endl;
        return false;
    }
}

string FactNode::to_string() const {
    return string("FactNode: ") + literal;
}
