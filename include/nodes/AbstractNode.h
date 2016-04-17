#ifndef PROLOG_ABSTRACTNODE_H
#define PROLOG_ABSTRACTNODE_H

namespace prolog {
    namespace nodes {   
        namespace types {
            enum NodeType {
                Abstract,
                Fact,
                Test
            };
        }
        
        class AbstractNode {
        public:
            AbstractNode(types::NodeType t) : type(t) {};
            virtual bool matches(AbstractNode const& n) = 0;
            virtual std::string to_string() = 0;
            const types::NodeType type;
        };
    }
}

#endif
