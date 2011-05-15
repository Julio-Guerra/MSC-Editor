#include "end-node.hh"

namespace msc
{
  void EndNode::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
