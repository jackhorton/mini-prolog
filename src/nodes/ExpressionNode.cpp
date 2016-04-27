#include <vector>
#include <string>
#include <iostream>

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
    
    std::cout << "aaaaaaaaaaaaaaaaaaaa" << std::endl;
    std::cout << "Context before evaluating ExpressionNode:\n" << context.debug_string() << std::endl;
    std::cout << "aaaaaaaaaaaaaaaaaaaa" << std::endl;
    
    Dictionary& dict = Dictionary::get();
    
    for (AbstractNode const* clause : clauses) {
        dict.resolve(*clause, context);
    }
    
    std::cout << "zzzzzzzzzzzzzzzzzzzz" << std::endl;
    std::cout << "Context after evaluating ExpressionNode:\n" << context.debug_string() << std::endl;
    std::cout << "zzzzzzzzzzzzzzzzzzzz" << std::endl;
    
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
