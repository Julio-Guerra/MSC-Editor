#include "complete-message.hh"

namespace msc
{
  void CompleteMessage::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
