#include <list>
#include <vector>
#include <string>
#include <iterator>

#include <cstdint>

#include "nodes/ArgumentsNode.h"
#include "nodes/AbstractNode.h"

using namespace prolog::nodes;
using namespace prolog;
using std::string;
using std::list;
using std::vector;

static vector<AbstractNode const*> list_to_vector(list<AbstractNode const*> const& original) {
    vector<AbstractNode const*> ret;
    ret.reserve(original.size());
    std::copy(original.begin(), original.end(), std::back_inserter(ret));
    
    return ret;
}

ArgumentsNode::ArgumentsNode(AbstractNode const* n) : AbstractNode(types::Arguments), args(1, n) {}

ArgumentsNode::~ArgumentsNode() {
    for (AbstractNode const* node : args) {
        delete node;
    }
}

ArgumentsNode* ArgumentsNode::push_back(AbstractNode const* n) {
    args.push_back(n);
    
    return this;
}

ArgumentsNode* ArgumentsNode::push_front(AbstractNode const* n) {
    args.push_front(n);
    
    return this;
}

bool ArgumentsNode::equals(AbstractNode const& n) const {
    if (n.type != types::Arguments) {
        return false;
    }
    
    ArgumentsNode const* other = static_cast<ArgumentsNode const*>(&n);
    
    if (args.size() != other->args.size()) {
        return false;
    }
    
    vector<AbstractNode const*> own_args = list_to_vector(args);
    vector<AbstractNode const*> other_args = list_to_vector(other->args);
    
    for (uint32_t i = 0; i < args.size(); i++) {
        if (!own_args[i]->equals(*other_args[i])) {
            return false;
        }
    }
    
    return true;
}

QueryContext& ArgumentsNode::resolve(AbstractNode const& n, QueryContext& context) const {
    if (n.type != types::Arguments) {
        return context.reject();
    }
    
    ArgumentsNode const& other = static_cast<ArgumentsNode const&>(n);
    
    if (args.size() != other.args.size()) {
        return context.reject();
    }
    
    vector<AbstractNode const*> own_args = list_to_vector(args);
    vector<AbstractNode const*> other_args = list_to_vector(other.args);
    uint32_t i = 0;
    uint32_t max = args.size();
    
    while (context.good() && i < max) {
        own_args[i]->resolve(*other_args[i], context);
        i++;
    }
    
    return context;
}

string ArgumentsNode::to_string() const {
    string ret;
    
    for (AbstractNode const* n : args) {
        ret += n->to_string() + ", ";
    }
    
    return ret;
}
