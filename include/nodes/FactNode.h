#ifndef PROLOG_FACTNODE_H
#define PROLOG_FACTNODE_H

#include <string>
#include <vector>

#include "nodes/AbstractNode.h"
#include "dictionary/QueryContext.h"

namespace prolog {
    class FactNode : public AbstractNode {
    public:
        FactNode(char const* lit);
        ~FactNode();
        std::string const& get_literal() const;
        bool equals(AbstractNode const& n) const override;
        QueryContext& resolve(AbstractNode const& query, QueryContext& context) const override;
        std::vector<std::string> get_variable_names() const override;
        std::string to_string() const override;
        std::string debug_string() const override;
    private:
        std::string literal;
    };
}

#endif
