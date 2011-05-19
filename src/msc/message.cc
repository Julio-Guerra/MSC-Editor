#include "message.hh"

namespace msc
{
  Message::Message(direction_enum direction, String* instance)
    : direction_ (direction), instance_ (instance)
  {
  }

  Message::~Message()
  {
  }

  void Message::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
