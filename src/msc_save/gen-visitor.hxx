#ifndef GEN_VISITOR_HXX_
# define GEN_VISITOR_HXX_

# include "msc/gen-visitor.hh"
# include "msc/ast.hh"

namespace msc
{
  template <typename E>
  void Visitor::accept(E* e)
  {
    if (e)
      e->accept(*this);
  }
} // namespace msc

#endif /* !GEN_VISITOR_HXX_ */
