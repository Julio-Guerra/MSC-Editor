#include "reference-node.hh"

namespace msc
{
  void ReferenceNode::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
