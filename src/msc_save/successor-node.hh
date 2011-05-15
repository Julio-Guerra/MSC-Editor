#ifndef SUCCESSOR_NODE_HH_
# define SUCCESSOR_NODE_HH_

# include <vector>
# include "msc/fwd.hh"

namespace msc
{
  class SuccessorNode
  {
    public:

    private:
      std::vector<NodeRelation*>        predecessors_;
  };
} // namespace msc

#endif /* !SUCCESSOR_NODE_HH_ */
