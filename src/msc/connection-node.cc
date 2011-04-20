#include "connection-node.hh"

namespace msc
{
  void ConnectionNode::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
