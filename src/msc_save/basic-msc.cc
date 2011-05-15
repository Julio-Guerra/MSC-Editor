#include "msc/basic-msc.hh"

namespace msc
{
  void BasicMsc::accept(Visitor& v)
  {
    v(*this);
  }
}
