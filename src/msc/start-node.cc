#include "start-node.hh"

namespace msc
{
  void StartNode::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
