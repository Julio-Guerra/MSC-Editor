#include "msc/document-head.hh"

namespace msc
{
  DocumentHead::DocumentHead(String*            kind,
                             Identifier*        id)
    : kind_ (kind), identifier_ (id)
  {
  }

  DocumentHead::~DocumentHead()
  {
  }

  void DocumentHead::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
