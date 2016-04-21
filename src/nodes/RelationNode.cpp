#include <string>
#include <memory>

#include "nodes/RelationNode.h"
#include "nodes/ArgumentsNode.h"

using namespace prolog::nodes;
using std::vector;
using std::string;

/*
 * RelationNodes own the AbstractNode objects pointed to by the arguments.
 * When this node is deleted/goes out of scope, its argument nodes will be deleted
 */
RelationNode::RelationNode(string name, ArgumentsNode const* args)
  : AbstractNode(types::Relation)
  , name(name)
  , arguments(args) {}

RelationNode::~RelationNode() {
    delete arguments;
}

string const& RelationNode::get_name() const {
    return name;
} 

bool RelationNode::matches(AbstractNode const& n) const {
    if (n.type == types::Relation) {
        RelationNode const* other = static_cast<RelationNode const*>(&n);

        if (name.compare(other->name) != 0 || !arguments->matches(*other->arguments)) {
            return false;
        }
        
        return true;
    } else {
        return false;
    }
}

std::string RelationNode::to_string() const {
    std::string ret("(RelationNode: "); 
    ret += "name: " + name + ", args: " + arguments->to_string() + ")";
    
    return ret;
}
