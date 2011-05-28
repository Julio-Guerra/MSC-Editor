#include "message.hh"

namespace msc
{
  Message::Message(String* label, Instance* from, Instance* to)
    : Labelable(*label), from_ (from), to_ (to)
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
