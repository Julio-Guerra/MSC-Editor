#include "high-msc.hh"

namespace msc
{
  void HighMsc::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
