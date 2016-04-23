#ifndef PROLOG_ABSTRACTNODE_H
#define PROLOG_ABSTRACTNODE_H

#include <string>

#include "dictionary/QueryContext.h"

namespace prolog {  
    namespace types {
        enum NodeType {
            Fact,
            Relation,
            Arguments,
            Variable
        };
    }
    
    class AbstractNode {
    public:
        AbstractNode(types::NodeType t) : type(t) {};
        virtual ~AbstractNode() {};
        virtual bool equals(AbstractNode const& n) const = 0;
        virtual QueryContext& resolve(AbstractNode const& n, QueryContext& context) const = 0;
        virtual std::string to_string() const = 0;
        const types::NodeType type;
    };
}

#endif
