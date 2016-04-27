#include <string>
#include <vector>

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

QueryContext& RelationNode::resolve(AbstractNode const& query, QueryContext& context) const {
    if (query.type != types::Relation || !context.good()) {
        return context.reject();
    }
    
    // this does not currently support binding a RelationNode to a variable
    RelationNode const& other = static_cast<RelationNode const&>(query);
    
    if (name.compare(other.name) != 0) {
        return context.reject();
    }
    
    return arguments->resolve(*other.arguments, context);
}

vector<string> RelationNode::get_variable_names() const {
    return arguments->get_variable_names();
}

string RelationNode::to_string() const {
    return string(name) + "(" + arguments->to_string() + ")";;
}

string RelationNode::debug_string() const {
    string ret("(RelationNode "); 
    ret += name + " " + arguments->debug_string() + ")";
    
    return ret;
}
