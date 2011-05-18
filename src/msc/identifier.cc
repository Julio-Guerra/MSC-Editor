#include "identifier.hh"

namespace msc
{
  Identifier::Identifier(String* qualifier, String* name)
    : qualifier_ (qualifier), name_ (name)
  {
  }

  Identifier::~Identifier()
  {
  }

  void Identifier::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace
