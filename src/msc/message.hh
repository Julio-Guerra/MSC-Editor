#ifndef MESSAGE_HH_
# define MESSAGE_HH_

# include "msc/fwd.hh"

# include "msc/ast.hh"
# include "msc/labelable.hh"
# include "msc/gen-visitor.hh"

namespace msc
{
  class Message : public Ast, public Labelable
  {
    public:
      // temporary
      // 1) Use Labelable to name the message.
      // 2) The instance node holding "this" is the "from"; so we
      //    only need to know "to".
      Instance* to;
      // !temporary

      virtual void accept(Visitor&);
  };
}

#endif /* !MESSAGE_HH_ */
