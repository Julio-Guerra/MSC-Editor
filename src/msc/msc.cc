#include "msc/msc.hh"

namespace msc
{
  void Msc::accept(Visitor& v)
  {
    v(*this);
  }
}
