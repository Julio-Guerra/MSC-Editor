#ifndef STATEMENT_HH_
# define STATEMENT_HH_

# include "msc/ast.hh"

namespace msc
{
  /// \brief Abstract base class.
  class Statement : public virtual Ast
  {
  };
} // namespace msc

#endif /* !STATEMENT_HH_ */
