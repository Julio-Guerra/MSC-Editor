#include "msc-message.hh"

namespace msc
{
  void MscMessage::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
