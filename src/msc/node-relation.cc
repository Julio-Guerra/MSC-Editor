#include "node-relation.hh"

namespace msc
{
  void NodeRelation::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
