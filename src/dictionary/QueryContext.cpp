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

QueryContext& QueryContext::absorb(QueryContext const& other) {
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
    
    return *this;
}

QueryContext& QueryContext::set_working(uint32_t index) {
    working_index = index;
    
    return *this;
}

QueryContext& QueryContext::bind(VariableNode const& var, AbstractNode const* binding) {
    if (!solutions[working_index].good()) {
        return *this;
    }
    
    solutions[working_index].bind(var, binding);
    
    return *this;
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
            ret += solution.to_string();
        }
    }
    
    return ret;
}

bool QueryContext::good() const {
    return solutions[working_index].good();
}
