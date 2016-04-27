#include <string>
#include <vector>

#include "nodes/AbstractNode.h"
#include "nodes/FactNode.h"
#include "nodes/VariableNode.h"
#include "dictionary/QueryContext.h"

using namespace prolog;
using std::string;
using std::vector;

FactNode::FactNode(char const* lit) : AbstractNode(types::Fact), literal(string(lit)) {}

FactNode::~FactNode() {}

string const& FactNode::get_literal() const {
    return literal;
} 

bool FactNode::equals(AbstractNode const& n) const {
   if (n.type == types::Fact) {
        FactNode const& fact = static_cast<FactNode const&>(n);
        
        return (literal.compare(fact.literal) == 0);
    } else {
        return false;
    }
}

QueryContext& FactNode::resolve(AbstractNode const& query, QueryContext& context) const {
    if (query.type == types::Fact) {
        FactNode const& other = static_cast<FactNode const&>(query);
                
        if (literal.compare(other.literal) != 0) {
            return context.reject();
        }
        
        return context;
    } else if (query.type == types::Variable) {
        VariableNode const& other = static_cast<VariableNode const&>(query);
        
        return context.bind(other, this);
    } else {
        return context.reject();
    }
}

vector<string> FactNode::get_variable_names() const {
    return vector<string>();
}

string FactNode::to_string() const {
    return string(literal);
}

string FactNode::debug_string() const {
    return string("(FactNode ") + literal + ")";
}
