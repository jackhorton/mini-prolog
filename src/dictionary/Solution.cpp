#include <map>
#include <string>
#include <iostream>

#include "dictionary/Solution.h"
#include "nodes/AbstractNode.h"
#include "nodes/VariableNode.h"

using namespace prolog;
using std::pair;
using std::string;

Solution::Solution() : failed(false) {}

Solution& Solution::reject() {
    failed = true;
    
    std::cout << "Rejecting " << this->debug_string() << std::endl;

    return *this;
}

Solution& Solution::bind(VariableNode const& var, AbstractNode const* binding) {
    if (!this->good()) {
        return *this;
    }
    
    string variable_name = var.get_literal();
    auto alias = aliases.find(variable_name);
    if (alias != aliases.end()) {
        variable_name = alias->second;
    }
    
    auto existing_binding = bindings.find(variable_name);
    if (existing_binding != bindings.end() && !existing_binding->second->equals(*binding)) {
        return this->reject();
    }
    
    bindings.insert(pair<string, AbstractNode const*>(variable_name, binding));
    
    return *this;
}

Solution& Solution::set_external_vars(AbstractNode const& query) {
    external_vars = query.get_variable_names();
    
    return *this;
}

Solution& Solution::alias(string source, string target) {
    aliases.insert(pair<string, string>(source, target));
    
    return *this;
}

string Solution::to_string() const {
    string ret;
    
    if (bindings.size() < external_vars.size()) {
        ret = "Something went very wrong...";
        // so, something didnt actually go that wrong
        // i just dont handle singleton variables yet
        
        
        
        
        
        // because theyre bad
    } else if (failed) {
        ret = ""; // this shouldnt ever be called
    } else if (external_vars.size() == 0) {
        ret = "true";
    } else {
        for (auto& binding : bindings) {
            for (string const& exvar : external_vars) {
                if (exvar.compare(binding.first) == 0) {
                    ret += binding.first + ": " + binding.second->to_string();
                    if (&binding != &*bindings.rbegin()) {
                        ret += "\n";
                    }
                    break;
                }
            }
        }
    }

    return ret;
}

string Solution::debug_string() const {
    string ret("(Solution");
    for (auto& binding : bindings) {
        ret += " (Binding " + binding.first + " " + binding.second->debug_string() + ")";
    }
    for (auto& alias : aliases) {
        ret += " (Alias " + alias.first + " -> " + alias.second + ")";
    }
    ret += ")";
    
    return ret;
}

bool Solution::good() const {
    return !failed;
}

bool Solution::equals(Solution const& other) const {
    if (failed != other.failed) {
        return false;
    }
    
    for (auto& own_binding : bindings) {
        auto search = other.bindings.find(own_binding.first);
        if (search == other.bindings.end()) {
            return false;
        }
    }
    
    for (auto& own_alias : aliases) {
        auto search = other.aliases.find(own_alias.first);
        if (search == other.aliases.end()) {
            return false;
        }
    }
    
    return true;
}
