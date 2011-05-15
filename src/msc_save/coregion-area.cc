#include "coregion-area.hh"

namespace msc
{
  void CoregionArea::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
