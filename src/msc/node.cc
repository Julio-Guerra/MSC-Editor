#include "msc/node.hh"

namespace msc
{
  Node::~Node()
  {
  }

  void Node::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
