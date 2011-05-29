#ifndef MSC_HH_
# define MSC_HH_

# include "msc/ast.hh"
# include "msc/labelable.hh"

namespace msc
{
  /** \brief Abstract class for BasicMsc and HighMsc.
   */
  class Msc : public Ast
  {
  };
}

#endif /* !MSC_HH_ */
