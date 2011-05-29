#ifndef MSC_AST_HH_
# define MSC_AST_HH_

# include "msc/gen-visitor.hh"

namespace msc
{
  /// The pure abstract class implemented by every single node of the AST.
  class Ast
  {
    public:
      virtual ~Ast();

      virtual void accept(Visitor&) = 0;

    private:
  };
} // namespace msc

#endif /* !MSC_AST_HH_ */
