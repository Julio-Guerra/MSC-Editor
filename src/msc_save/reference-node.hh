#ifndef REFERENCE_NODE_HH_
# define REFERENCE_NODE_HH_

# include "msc/high-msc-node.hh"
# include "msc/successor-node.hh"
# include "msc/predecessor-node.hh"
# include "msc/gen-visitor.hh"

namespace msc
{
  class ReferenceNode : public HighMscNode,
                        public PredecessorNode,
                        public SuccessorNode
  {
    public:
      virtual void accept(Visitor&);

    private:
      Msc*      msc_;
  };
} // namespace msc

#endif /* !REFERENCE_NODE_HH_ */
