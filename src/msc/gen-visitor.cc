#include "gen-visitor.hh"

namespace msc
{
  void GenVisitor::operator()(MscElement& e)
  {
    e.accept(*this);
  }
} // namespace msc
