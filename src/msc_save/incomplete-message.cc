#include "msc/incomplete-message.hh"

namespace msc
{
  void IncompleteMessage::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
