#include <string>
#include <memory>

#include "nodes/AbstractNode.h"
#include "dictionary.h"

using namespace prolog;
using std::string;
using std::unique_ptr;
using std::vector;

Dictionary& Dictionary::get() {
    static Dictionary instance;
    
    return instance;
}

Dictionary& Dictionary::insert(nodes::AbstractNode const& n) {
    clauses.push_back(&n);
    
    return *this;
}

vector<nodes::AbstractNode const*> const* Dictionary::find(nodes::AbstractNode const& n) const {
    vector<nodes::AbstractNode const*> *matches = new vector<nodes::AbstractNode const*>();
    
    for (nodes::AbstractNode const* clause : clauses) {
        if (n.matches(*clause)) {
            matches->push_back(clause);
        }
    }
    
    return matches;
}
