#include "msc/event.hh"

namespace msc
{
  Event::Event()
  {
  }

  Event::~Event()
  {
  }

  void Event::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
