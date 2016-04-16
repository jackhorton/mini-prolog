#include <string>
#include <memory>
#include <vector>

#include "nodes/AbstractNode.h"
#include "dictionary.h"

using namespace prolog;
using namespace prolog::nodes;
using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::move;
using std::vector;

Dictionary& Dictionary::get() {
    static Dictionary instance;
    
    return instance;
}

Dictionary& Dictionary::insert(nodes::AbstractNode* n) {
    clauses.push_back(shared_ptr<AbstractNode>(n));
    
    return *this;
}

unique_ptr<vector<shared_ptr<AbstractNode>>> Dictionary::find(AbstractNode& n) const {
    unique_ptr<vector<shared_ptr<AbstractNode>>> matches(new vector<shared_ptr<AbstractNode>>());
    
    for (auto clause : clauses) {
        if (n.matches(*clause)) {
            matches->push_back(clause);
        }
    }
    
    return matches;
}
