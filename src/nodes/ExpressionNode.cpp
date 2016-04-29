#include <vector>
#include <string>

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
        vector<QueryContext*> leaves = context.get_leaves();
        
        for (QueryContext* leaf : leaves) {
            dict.resolve(*clause, *leaf);
        
            // collapse children will get rid of duplicates that occur from multi-clause expressions
            // if two clauses bind a single variable to the same thing, it doesnt matter,
            // since any children of either resulting context will follow a different but functionally
            // equal path up the tree to get the result
            leaf->collapse_children();
        }
    }
    
    return context;
}

vector<string> ExpressionNode::get_variable_names() const {
    vector<string> ret;
    
    for (AbstractNode const* clause : clauses) {
        vector<string> clausevars = clause->get_variable_names();
        if (!clausevars.empty()) {
            ret.reserve(ret.size() + clausevars.size());
            ret.insert(ret.end(), clausevars.begin(), clausevars.end());
        }
    }
    
    return ret;
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
