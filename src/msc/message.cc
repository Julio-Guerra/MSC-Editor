#include "message.hh"

namespace msc
{
  Message::~Message()
  {

  }

  void Message::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
