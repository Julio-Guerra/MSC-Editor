#include "high-msc-node.hh"

namespace msc
{
  void HighMscNode::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
