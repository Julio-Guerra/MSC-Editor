#ifndef PREDECESSOR_NODE_HH_
# define PREDECESSOR_NODE_HH_

# include <vector>
# include "msc/fwd.hh"

namespace msc
{
  class PredecessorNode
  {
    public:

    private:
      std::vector<NodeRelation*>        successors_;
  };
} // namespace msc

#endif /* !PREDECESSOR_NODE_HH_ */
