#include <string>
#include <memory>

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

bool FactNode::matches(AbstractNode const& n) const {
    if (n.type == types::Fact) {
        FactNode const* fact = static_cast<FactNode const*>(&n);
        return (literal.compare(fact->literal) == 0);
    } else {
        return false;
    }
}

string FactNode::to_string() const {
    return string("FactNode: ") + literal;
}
