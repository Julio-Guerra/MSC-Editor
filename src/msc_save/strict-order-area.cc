#include "msc/strict-order-area.hh"

namespace msc
{
  void StrictOrderArea::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
