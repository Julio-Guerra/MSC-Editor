#include "msc/text-definition.hh"

namespace msc
{
  TextDefinition::TextDefinition(String*        text)
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
