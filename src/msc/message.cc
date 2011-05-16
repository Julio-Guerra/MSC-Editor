#include "message.hh"

namespace msc
{
  void Message::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
