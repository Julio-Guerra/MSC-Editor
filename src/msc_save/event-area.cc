#include "msc/event-area.hh"

namespace msc
{
  void EventArea::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
