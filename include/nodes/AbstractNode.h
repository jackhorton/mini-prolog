#ifndef PROLOG_ABSTRACTNODE_H
#define PROLOG_ABSTRACTNODE_H

#include <string>
#include <vector>

#include "dictionary/QueryContext.h"

namespace prolog {  
    namespace types {
        enum NodeType {
            Fact,
            Relation,
            Arguments,
            Variable,
            Rule,
            Expression
        };
    }
    
    class AbstractNode {
    public:
        AbstractNode(types::NodeType t) : type(t) {};
        virtual ~AbstractNode() {};
        virtual bool equals(AbstractNode const& n) const = 0;
        virtual QueryContext& resolve(AbstractNode const& query, QueryContext& context) const = 0;
        virtual std::vector<std::string> get_variable_names() const = 0;
        virtual std::string to_string() const = 0;
        virtual std::string debug_string() const = 0;
        const types::NodeType type;
    };
}

#endif
