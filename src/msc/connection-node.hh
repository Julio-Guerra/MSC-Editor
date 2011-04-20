#ifndef CONNECTION_NODE_HH_
# define CONNECTION_NODE_HH_

# include "msc/high-msc-node.hh"
# include "msc/predecessor-node.hh"
# include "msc/successor-node.hh"
# include "msc/gen-visitor.hh"

namespace msc
{
  class ConnectionNode : public HighMscNode,
                         public PredecessorNode,
                         public SuccessorNode
  {
    public:
      virtual void accept(Visitor&);
  };
} // namespace msc

#endif /* !CONNECTION_NODE_HH_ */
