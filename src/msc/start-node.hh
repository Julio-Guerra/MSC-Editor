#ifndef START_NODE_HH_
# define START_NODE_HH_

# include "msc/high-msc-node.hh"
# include "msc/predecessor-node.hh"

namespace msc
{
  class StartNode : public HighMscNode, public PredecessorNode
  {
    public:
      virtual void accept(Visitor&);
  };
} // namespace msc

#endif /* !START_NODE_HH_ */
