#include "msc/gen-visitor.hh"

namespace msc
{
  void GenVisitor::operator()(Ast& e)
  {
    e.accept(*this);
  }
} // namespace msc
