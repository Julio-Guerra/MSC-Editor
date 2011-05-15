#include "msc/event.hh"

namespace msc
{
  void Event::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
