#include <string>
#include <memory>

#include "nodes/FactNode.h"

using namespace prolog::nodes;
using std::unique_ptr;
using std::move;
using std::string;

FactNode(std::unique_ptr<std::string> lit) : literal(std::move(lit)) {}

string const& FactNode::get_literal() const {
    return literal;
} 

bool FactNode::matches(FactNode const& n) const {
    return (literal->compare(n.get_literal()) == 0);
}

bool FactNode::matches(AbstractNode const& n) const {
    return false;
}
