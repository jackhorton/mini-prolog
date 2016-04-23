#include <map>
#include <string>

#include "dictionary/QueryContext.h"
#include "nodes/AbstractNode.h"
#include "nodes/VariableNode.h"

using namespace prolog;
using std::pair;
using std::string;

QueryContext::QueryContext() : failed(false) {}

QueryContext& QueryContext::reject() {
    failed = true;
    
    return *this;
}

QueryContext& QueryContext::bind(VariableNode const& var, AbstractNode const* binding) {
    if (this->failed) {
        return *this;
    }
    
    bindings.insert(pair<string, AbstractNode const*>(var.get_literal(), binding));
    
    return *this;
}

string QueryContext::to_string() const {
    string ret;
    
    for (auto& binding : bindings) {
        ret += binding.first + ": " + binding.second->to_string() + "\n";
    }
    
    return ret;
}

bool QueryContext::good() const {
    return !failed;
}
