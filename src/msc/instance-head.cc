#include "instance-head.hh"

namespace msc
{
  InstanceHead::InstanceHead(String*            kind,
                             Identifier*        identifier,
                             String*            substructure)
    : kind_ (kind),
      identifier_ (identifier),
      substructure_ (substructure)
  {
  }

  InstanceHead::~InstanceHead()
  {
  }

  void InstanceHead::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
