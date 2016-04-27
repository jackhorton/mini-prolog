#include <string>
#include <vector>

#include "nodes/AbstractNode.h"
#include "nodes/VariableNode.h"
#include "dictionary/QueryContext.h"

using namespace prolog;
using std::string;
using std::vector;

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

QueryContext& VariableNode::resolve(AbstractNode const& query, QueryContext& context) const {
    if (query.type == types::Variable) {
        auto other = static_cast<VariableNode const&>(query);
        
        context.working().alias(literal, other.literal);
    } else {
        context.working().bind(*this, &query);
    }
    
    return context;
}

vector<string> VariableNode::get_variable_names() const {
    return vector<string> {literal};
}

string VariableNode::to_string() const {
    return string(literal);
}

string VariableNode::debug_string() const {
    return string("(VariableNode ") + literal + ")";
}
