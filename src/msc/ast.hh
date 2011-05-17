#ifndef AST_HH_
# define AST_HH_

# include "msc/gen-visitor.hh"

namespace msc
{
  /** The pure abstract class implemented by every single node of the AST.
   */
  class Ast
  {
    public:
      /** A very simple way to enforce at least the first generation
       * to implement the dtor.
       * By the way, a dtor from a class part of a hierarchy *must*
       * be virtual to be able to call childs'
       * dtors.
       */
      virtual ~Ast() {}

      virtual void accept(Visitor&) = 0;

    private:
  };
} // namespace msc

#endif /* !AST_HH_ */
