#include "instance-head.hh"

namespace msc
{
  InstanceHead::InstanceHead(String*            kind,
                             Identifier*        identifier,
                             bool               decomposed,
                             String*            substructure)
    : kind_ (kind),
      identifier_ (identifier),
      decomposed_ (decomposed),
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
