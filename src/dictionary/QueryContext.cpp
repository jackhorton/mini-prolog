#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cstddef>
#include <iostream>

#include "dictionary/QueryContext.h"
#include "nodes/AbstractNode.h"
#include "nodes/VariableNode.h"

using namespace prolog;
using std::string;
using std::vector;
using std::pair;

QueryContext::QueryContext() : status(true), parent(nullptr) {}
QueryContext::QueryContext(QueryContext const* parent) : status(true), parent(parent) {}

QueryContext::~QueryContext() {
    for (QueryContext* ctx : children) {
        delete ctx;
    }
}

QueryContext& QueryContext::reject() {
    status = false;
    
    return *this;
}

QueryContext& QueryContext::alias(string source, string target) {
    aliases.insert(pair<string, string>(source, target));
    
    return *this;
}

QueryContext& QueryContext::bind(VariableNode const& var, AbstractNode const* binding) {
    if (!this->good()) {
        return *this;
    }
    
    auto found = this->find(var);
    string variable_name = found.first;
    AbstractNode const* bound_node = found.second;
    
    if (bound_node == nullptr) {
        bindings.insert(pair<string, AbstractNode const*>(variable_name, binding));
    } else if (!bound_node->equals(*binding)) {
        // found a corresponding binding in the ancestry that doesn't match this one
        return this->reject();
    }
    
    // this means we found an existing binding but its equal to what we are currently trying to bind to so ¯\_(ツ)_/¯
    return *this;
}

pair<string, AbstractNode const*> QueryContext::find(VariableNode const& var) const {
    string const& variable_name = this->resolve_variable_name(var.get_literal());
    AbstractNode const* bound_node;
    
    auto existing_binding = bindings.find(variable_name);
    if (existing_binding != bindings.end()) {
        bound_node = existing_binding->second;
    }
    
    if (parent == nullptr) {
        bound_node = nullptr;
    } else {
        return parent->find(var);
    }
    
    return make_pair(variable_name, bound_node);
}

QueryContext& QueryContext::create_child() {
    QueryContext* ctx = new QueryContext(this);
    
    children.push_back(ctx);
    
    return *ctx;
}

string const& QueryContext::resolve_variable_name(string const& original_name) const {
    auto alias = aliases.find(original_name);
    if (alias != aliases.end()) {
        return alias->second;
    }
    
    if (parent != nullptr) {
        return parent->resolve_variable_name(original_name);
    } else {
        return original_name;
    }
}

string QueryContext::to_string() const {
    string ret;
    
    // early exits
    if (!status) {
        // failed
        // should never be called on children, so we can append the period
        return "false.";
    } else if (parent == nullptr) {
        bool is_first = false;
        
        for (QueryContext* ctx : children) {
            if (!ctx->good()) {
                continue;
            }
            
            if (!is_first) {
                is_first = true;
            } else {
                ret += ";\n";
            }
            
            ret += ctx->to_string();
        }
        
        ret += ".";
        
        return ret;
    }
    
    if (bindings.size() == 0) {
        ret = "true";
    } else {
        for (auto& binding : bindings) {
            ret += binding.first + ": " + binding.second->to_string();
            if (&binding != &*bindings.rbegin()) {
                ret += "\n";
            }
        }
        
        for (QueryContext* ctx : children) {
            ret += ctx->to_string();
        }
    }
    
    return ret;
}

string QueryContext::debug_string() const {
    string ret("(QueryContext");
    if (!this->good()) {
        ret += " failed)";
        return ret;
    }
    for (auto& binding : bindings) {
        ret += " (Binding " + binding.first + " " + binding.second->debug_string() + ")";
    }
    for (auto& alias : aliases) {
        ret += " (Alias " + alias.first + " -> " + alias.second + ")";
    }
    for (QueryContext* ctx : children) {
        ret += " " + ctx->debug_string();
    }
    ret += ")";
    
    return ret;
}

void QueryContext::prompt() const {
    std::cout << this->to_string() << std::endl;
}

bool QueryContext::good() const {
    return status;
}
