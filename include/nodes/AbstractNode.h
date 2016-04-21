#ifndef PROLOG_ABSTRACTNODE_H
#define PROLOG_ABSTRACTNODE_H

namespace prolog {
    namespace nodes {   
        namespace types {
            enum NodeType {
                Abstract,
                Fact,
                Relation,
                Arguments
            };
        }
        
        class AbstractNode {
        public:
            AbstractNode(types::NodeType t) : type(t) {};
            virtual ~AbstractNode() {};
            virtual bool matches(AbstractNode const& n) const = 0;
            virtual std::string to_string() const = 0;
            const types::NodeType type;
        };
    }
}

#endif
