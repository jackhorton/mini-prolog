#include <string>
#include <vector>
#include <iostream>

#include "nodes/AbstractNode.h"
#include "nodes/RuleNode.h"

using namespace prolog;
using std::string;
using std::vector;

RuleNode::RuleNode(AbstractNode const* head, AbstractNode const* body) 
  : AbstractNode(types::Rule)
  , head(head)
  , body(body) {}

RuleNode::~RuleNode() {
    delete head;
    delete body;
}

bool RuleNode::equals(AbstractNode const& other) const {
    return false;
}

QueryContext& RuleNode::resolve(AbstractNode const& query, QueryContext& context) const {
    head->resolve(query, context);
    body->resolve(query, context);
    
    std::cout << "rrrrrrrrrrrrrrrrrrrrrrrrrrrrr" << std::endl;
    std::cout << "Context after resolving RuleNode:\n" << context.debug_string() << std::endl;
    std::cout << "rrrrrrrrrrrrrrrrrrrrrrrrrrrrr" << std::endl;
    
    return context;
}

vector<string> RuleNode::get_variable_names() const {
    return head->get_variable_names();
}

string RuleNode::to_string() const {
    return "";
}

string RuleNode::debug_string() const {
    return string("(RuleNode ") + head->debug_string() + " " + body->debug_string() + ")";
}
