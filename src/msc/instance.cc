#include "instance.hh"

namespace msc
{
  Instance::Instance(const Label& label)
    : Labelable (label)
  {
  }

  Instance::~Instance()
  {
  }

  void Instance::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
