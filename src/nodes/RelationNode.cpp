#include <string>

#include "nodes/RelationNode.h"
#include "nodes/ArgumentsNode.h"
#include "dictionary/QueryContext.h"

using namespace prolog;
using std::vector;
using std::string;

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

bool RelationNode::equals(AbstractNode const& n) const {
    if (n.type == types::Relation) {
        RelationNode const* other = static_cast<RelationNode const*>(&n);

        if (name.compare(other->name) != 0 || !arguments->equals(*other->arguments)) {
            return false;
        }
        
        return true;
    } else {
        return false;
    }
}

QueryContext& RelationNode::resolve(AbstractNode const& n, QueryContext& context) const {
    if (n.type != types::Relation) {
        return context.reject();
    }
    
    RelationNode const& other = static_cast<RelationNode const&>(n);
    
    if (name.compare(other.name) != 0) {
        return context.reject();
    }
    
    return arguments->resolve(*other.arguments, context);
}

string RelationNode::to_string() const {
    return string(name) + "(" + arguments->to_string() + ")";;
}

string RelationNode::debug_string() const {
    string ret("(RelationNode "); 
    ret += name + " " + arguments->debug_string() + ")";
    
    return ret;
}
