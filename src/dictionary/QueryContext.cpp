#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cstddef>
#include <iostream>
#include <cstdint>

#include "dictionary/QueryContext.h"
#include "nodes/AbstractNode.h"
#include "nodes/VariableNode.h"

using namespace prolog;
using std::string;
using std::vector;
using std::pair;
using std::uint32_t;

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
    
    auto found = this->find(this->resolve_variable_name(var.get_literal()));
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

pair<string, AbstractNode const*> QueryContext::find(string const& variable_name) const {
    AbstractNode const* bound_node = nullptr;
    
    auto existing_binding = bindings.find(variable_name);
    if (existing_binding != bindings.end()) {
        bound_node = existing_binding->second;
    }
    
    if (bound_node == nullptr && parent != nullptr) {
        return parent->find(variable_name);
    }
    
    return make_pair(variable_name, bound_node);
}

QueryContext& QueryContext::create_child() {
    QueryContext* ctx = new QueryContext(this);
    
    children.push_back(ctx);
    
    return *ctx;
}

QueryContext& QueryContext::collapse_children() {
    vector<QueryContext*> collapsed;
    
    // TODO: fix memory leak
    for (uint32_t i = 0; i < children.size(); i++) {
        QueryContext* cur = children[i];
        bool has_later_equivalent = false;
        
        // skip bad contexts early
        if (!cur->good()) {
            delete cur;
            cur = nullptr;
            continue;
        }
        
        for (uint32_t k = i + 1; k < children.size(); k++) {
            if (cur->equals(*children[k])) {
                has_later_equivalent = true;
                break;
            }
        }
        
        if (!has_later_equivalent) {
            collapsed.push_back(cur);
        } else {
            delete cur;
            cur = nullptr;
            continue;
        }
    }
    
    children.clear();
    children.reserve(collapsed.size());
    children.insert(children.begin(), collapsed.begin(), collapsed.end());
    
    return *this;
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
    if (parent == nullptr) {
        return this->to_root_string();
    } else {
        vector<string> temp;
        return this->to_child_string(temp);
    }
}

std::string QueryContext::to_root_string() const {
    bool is_first = false;
    string ret;
        
    for (QueryContext* ctx : children) {
        if (!ctx->good()) {
            continue;
        }
        
        if (!is_first) {
            is_first = true;
        } else {
            ret += ";\n";
        }
        
        ret += ctx->to_child_string(external_vars);
    }
    
    if (!is_first) {
        // no successful children
        ret = "false.";
    } else {
        ret += ".";
    }
    
    return ret;
}

std::string QueryContext::to_child_string(vector<string> const& important_vars) const {
    string ret;
    
    if (!status) {
        return ret;
    } else if (children.size() != 0) {
        for (QueryContext* ctx : children) {
            string child_string = ctx->to_child_string(important_vars);
            if (child_string.size() > 0) {
                ret += child_string;
                if (ctx != children.back()) {
                    ret += "\n";
                }
            }
        }
        
        return ret;
    }
    
    // we will only start adding to the string if this is a leaf
    if (important_vars.size() == 0) {
        ret = "true";
    }
    
    bool is_first = true;
    for (string const& var : important_vars) {
        auto binding = this->find(var);
        if (is_first) {
            is_first = true;
        } else {
            ret += ";\n";
        }
        
        if (binding.second != nullptr) {
            ret += var + ": " + binding.second->to_string();
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

void QueryContext::set_external_vars(AbstractNode const& query) {
    external_vars = query.get_variable_names();
}

void QueryContext::prompt() const {
    std::cout << this->to_string() << std::endl;
}

bool QueryContext::equals(QueryContext const& other) const {
    if (bindings.size() != other.bindings.size()) {
        return false;
    }
    
    auto own_binding = bindings.begin();
    auto other_binding = other.bindings.begin();
    
    while (own_binding != bindings.end()) {
        // maps are sorted, so going through linearly should be fine
        if (own_binding->first.compare(other_binding->first) != 0) {
            return false;
        }
        
        if (!own_binding->second->equals(*other_binding->second)) {
            return false;
        }
        
        own_binding++;
        other_binding++;
    }
    
    // aliases can be compared using == because its a map<string, string>, and strings can be compared properly
    // bindings, as a map<string, Node*>, was just checking pointer equality, which was not enough
    return (status == other.status && aliases == other.aliases);
}

bool QueryContext::good() const {
    return status;
}
