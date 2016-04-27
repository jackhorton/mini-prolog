#include <string>
#include <vector>
#include <cstdint>

#include "dictionary/QueryContext.h"
#include "dictionary/Solution.h"
#include "nodes/AbstractNode.h"
#include "nodes/VariableNode.h"

using namespace prolog;
using std::string;
using std::vector;
using std::uint32_t;

QueryContext::QueryContext(uint32_t initial) : solutions(initial, Solution()), working_index(0) {}
QueryContext::QueryContext(QueryContext const& other) : solutions(other.solutions), working_index(other.working_index) {}

QueryContext& QueryContext::reject() {
    return this->reject(working_index);
}

QueryContext& QueryContext::reject(uint32_t solution_index) {
    solutions.at(solution_index).reject();
    
    return *this;
}

QueryContext QueryContext::diff(QueryContext const& other) const {
    QueryContext ret(0);
    
    for (Solution const& own_solution : solutions) {
        bool should_insert = false;
        
        for (Solution const& input_solution : other.solutions) {
            if (own_solution.equals(input_solution)) {
                should_insert = true;
                break;
            }
        }
        
        if (!own_solution.good()) {
            should_insert = true;
        }
        
        if (!should_insert) {
            ret.solutions.push_back(own_solution);
        }
    }
    
    return ret;
}

QueryContext& QueryContext::absorb(QueryContext& other) {
    solutions.reserve(solutions.size() + other.solutions.size());
    solutions.insert(solutions.end(), other.solutions.begin(), other.solutions.end());
    
    return *this;
}

QueryContext& QueryContext::trim() {
    uint32_t solutions_size = solutions.size();
    vector<Solution> trimmed;
    
    for (uint32_t i = 0; i < solutions_size; i++) {
        if (solutions[i].good()) {
            trimmed.push_back(solutions[i]);
        } else {
            if (i < working_index) {
                working_index -= 1;
            } else if (i == working_index) {
                working_index = 0; // uhhh idk what happens here...
            }
        }
    }
    
    solutions = trimmed;
    
    return *this;
}

QueryContext& QueryContext::set_working(uint32_t index) {
    working_index = index;
    
    return *this;
}

QueryContext& QueryContext::bind(VariableNode const& var, AbstractNode const* binding) {
    solutions[working_index].bind(var, binding);
    
    return *this;
}

Solution& QueryContext::working() {
    return solutions[working_index];
}

uint32_t QueryContext::solution_count() const {
    return solutions.size();
}

string QueryContext::to_string() const {
    string ret;
    
    if (solutions.size() == 0) {
        ret = "false.";
    } else {
        for (Solution const& solution : solutions) {
            if (!solution.good()) {
                continue;
            }
            
            ret += solution.to_string();
            if (&solution == &solutions.back()) {
                ret += ".";
            } else {
                ret += ";\n";
            }
        }
    }
    
    return ret;
}

string QueryContext::debug_string() const {
    string ret("(QueryContext");
    
    for (Solution const& solution : solutions) {
        ret += " " + solution.debug_string();
    }
    
    ret += ")";
    
    return ret;
}

bool QueryContext::good() const {
    return solutions[working_index].good();
}
