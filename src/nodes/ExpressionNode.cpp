#include <vector>

#include "dictionary/Dictionary.h"
#include "nodes/AbstractNode.h"
#include "nodes/ExpressionNode.h"

using namespace prolog;
using std::string;
using std::vector;

ExpressionNode::ExpressionNode(AbstractNode const* initial) : AbstractNode(types::Expression) {
    clauses.push_back(initial);
}

ExpressionNode::~ExpressionNode() {
    for (AbstractNode const* clause : clauses) {
        delete clause;
    }
}

ExpressionNode* ExpressionNode::add_clause(AbstractNode const* clause) {
    clauses.push_back(clause);
    
    return this;
}

bool ExpressionNode::equals(AbstractNode const& other) const {
    return false; // ExpressionNodes should never be directly compared
}

QueryContext& ExpressionNode::resolve(AbstractNode const& query, QueryContext& context) const {
    if (!context.good()) {
        return context;
    }
    
    Dictionary& dict = Dictionary::get();
    
    for (AbstractNode const* clause : clauses) {
        dict.resolve(*clause, context);
    }
    
    return context;
}

string ExpressionNode::to_string() const {
    return "";
}

string ExpressionNode::debug_string() const {
    string ret("(ExpressionNode ");
    for (AbstractNode const* clause : clauses) {
        ret += clause->debug_string();
    }
    ret += ")";
    
    return ret;
}
