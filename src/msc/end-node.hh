#ifndef END_NODE_HH_
# define END_NODE_HH_

# include "msc/high-msc-node.hh"
# include "msc/successor-node.hh"
# include "msc/gen-visitor.hh"


namespace msc
{
  class EndNode : public HighMscNode, public SuccessorNode
  {
    public:
      virtual void accept(Visitor&);
  };
} // namespace msc


#endif /* !END_NODE_HH_ */
