#include <string>
#include <memory>
#include <iostream>

#include "nodes/TestNode.h"

using namespace prolog::nodes;
using std::unique_ptr;
using std::move;
using std::string;

TestNode::TestNode(char const* lit) : AbstractNode(types::Test), literal(new string(lit)) {}

string const& TestNode::get_literal() const {
    return *literal;
} 

bool TestNode::matches(AbstractNode const& n) {
    if (n.type == types::Test) {
        TestNode const* test = static_cast<TestNode const*>(&n);
        return (literal->compare(test->get_literal()) == 0);
    } else {
        return false;
    }
}
