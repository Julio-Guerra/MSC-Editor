#ifndef NODE_RELATION_HH_
# define NODE_RELATION_HH_

# include "msc/msc-element.hh"
# include "msc/gen-visitor.hh"
# include "msc/predecessor-node.hh"
# include "msc/successor-node.hh"

namespace msc
{
  class NodeRelation : public MscElement
  {
    public:
      virtual void accept(Visitor&);

    private:
      SuccessorNode*    successor_;

      PredecessorNode*  predecssor_;
  };
} // namespace msc

#endif /* !NODE_RELATION_HH_ */
