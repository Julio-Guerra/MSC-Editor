#include "msc/strict-event.hh"

namespace msc
{
  void StrictEvent::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
