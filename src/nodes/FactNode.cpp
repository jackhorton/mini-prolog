#include <string>
#include <memory>
#include <iostream>

#include "nodes/FactNode.h"

using namespace prolog::nodes;
using std::unique_ptr;
using std::move;
using std::string;

FactNode::FactNode(char const* lit) : AbstractNode(types::Fact), literal(new string(lit)) {}

string const& FactNode::get_literal() const {
    return *literal;
} 

bool FactNode::matches(AbstractNode const& n) {
    if (n.type == types::Fact) {
        FactNode const* fact = static_cast<FactNode const*>(&n);
        return (literal->compare(fact->get_literal()) == 0);
    } else {
        return false;
    }
}
