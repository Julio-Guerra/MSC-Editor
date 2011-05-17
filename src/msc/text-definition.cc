#include "msc/text-definition.hh"

namespace msc
{
  TextDefinition::TextDefinition(pString text)
    : text_ (text)
  {
  }

  TextDefinition::~TextDefinition()
  {
  }

  void TextDefinition::accept(Visitor& v)
  {
    v(*this);
  }
}
