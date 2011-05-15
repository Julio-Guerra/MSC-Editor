#ifndef NODE_HH_
# define NODE_HH_

# include "msc/ast.hh"
# include "msc/gen-visitor.hh"

namespace msc
{
  class Node : public Ast
  {
    public:
      /** \name Ctor & Dtor.
       * \{ */
      virtual ~Node();
      /** \} */

      virtual void      accept(Visitor&);


  }
} // namespace msc

#endif /* !NODE_HH_ */
