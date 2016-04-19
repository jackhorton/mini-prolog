#include <string>
#include <memory>
#include <iostream>

#include "nodes/RelationNode.h"

using namespace prolog::nodes;
using std::vector;
using std::string;

/*
 * RelationNodes own the AbstractNode objects pointed to by the arguments.
 * When this node is deleted/goes out of scope, its argument nodes will be deleted
 */
RelationNode::RelationNode(string name, vector<AbstractNode*> args) : 
    AbstractNode(types::Relation), 
    name(name), 
    arguments(args) {}

RelationNode::~RelationNode() {
    for (AbstractNode* node : arguments) {
        delete node;
    }
}

string const& RelationNode::get_name() const {
    return name;
} 

bool RelationNode::matches(AbstractNode const& n) {
    if (n.type == types::Relation) {
        RelationNode const* other = static_cast<RelationNode const*>(&n);

        std::cout << "Matching " << this->to_string() << " vs " << other->to_string() << std::endl;

        if (arguments.size() != other->arguments.size() || name.compare(other->name) != 0) {
            std::cout << "size or name incorrect" << std::endl;
            return false;
        }
        
        for (std::uint32_t i = 0; i < arguments.size(); i++) {
            if (!arguments[i]->matches(*(other->arguments[i]))) {
                std::cout << "argument " << other->arguments[i]->to_string() << " doesnt match" << std::endl;
                return false;
            }
        }
        
        return true;
    } else {
        return false;
    }
}

std::string RelationNode::to_string() const {
    std::string ret("RelationNode: "); 
    ret += name + "(";
    for (AbstractNode* arg : arguments) {
        ret += arg->to_string() + ", ";
    }
    ret += ")";
    
    return ret;
}
