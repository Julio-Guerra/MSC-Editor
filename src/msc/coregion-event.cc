#include "msc/coregion-event.hh"

namespace msc
{
  void CoregionEvent::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
