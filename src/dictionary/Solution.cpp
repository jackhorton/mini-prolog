#include <map>
#include <string>

#include "dictionary/Solution.h"
#include "nodes/AbstractNode.h"
#include "nodes/VariableNode.h"

using namespace prolog;
using std::pair;
using std::string;

Solution::Solution() : failed(false) {}

Solution& Solution::reject() {
    failed = true;
    
    return *this;
}

Solution& Solution::bind(VariableNode const& var, AbstractNode const* binding) {
    if (this->failed) {
        return *this;
    }
    
    bindings.insert(pair<string, AbstractNode const*>(var.get_literal(), binding));
    
    return *this;
}

string Solution::to_string() const {
    string ret;
    
    if (bindings.size() == 0 && !failed) {
        ret = "true";
    } else if (failed) {
        ret = "";
    } else {
        for (auto& binding : bindings) {
            ret += binding.first + ": " + binding.second->to_string() + "\n";
        }
    }
    
    return ret;
}

bool Solution::good() const {
    return !failed;
}
