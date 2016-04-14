#include <string>
#include <memory>

#include "nodes/FactNode.h"

using namespace prolog::nodes;
using std::unique_ptr;
using std::move;
using std::string;

FactNode::FactNode(unique_ptr<string> lit) : literal(move(lit)) {}

string const& FactNode::get_literal() const {
    return *literal;
} 

bool FactNode::matches(FactNode const& n) const {
    return (literal->compare(n.get_literal()) == 0);
}

bool FactNode::matches(AbstractNode const& n) const {
    return false;
}
