#include "instance.hh"

namespace msc
{
  void Instance::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
