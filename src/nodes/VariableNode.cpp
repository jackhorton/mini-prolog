#include <string>

#include "nodes/AbstractNode.h"
#include "nodes/VariableNode.h"
#include "dictionary/QueryContext.h"

using namespace prolog::nodes;
using namespace prolog;
using std::move;
using std::string;

VariableNode::VariableNode(char const* lit) : AbstractNode(types::Variable), literal(string(lit)) {}

VariableNode::~VariableNode() {}

string const& VariableNode::get_literal() const {
    return literal;
} 

bool VariableNode::equals(AbstractNode const& n) const {
   if (n.type == types::Variable) {
        VariableNode const& variable = static_cast<VariableNode const&>(n);
        
        return (literal.compare(variable.literal) == 0);
    } else {
        return false;
    }
}

QueryContext& VariableNode::resolve(AbstractNode const& n, QueryContext& context) const {
    if (n.type == types::Variable) {
        // can a variable resolve to another variable? probably but not right now
        return context.reject();
    } else {
        return context.bind(*this, &n);
    }
}

string VariableNode::to_string() const {
    return string("VariableNode: ") + literal;
}
