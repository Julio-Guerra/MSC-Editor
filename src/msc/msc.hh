#ifndef MSC_HH_
# define MSC_HH_

# include <vector>
# include "msc/ast.hh"
# include "msc/labelable.hh"
# include "msc/gen-visitor.hh"
# include "msc/instance.hh"

namespace msc
{
  class Msc: public Ast, public Labelable
  {
    public:
      // temporary
      // 1) use labelable interface to get the label of this node
      // i.e. the name of the Msc.

      // 2) Vector of instances of this Msc.
      std::vector<Instance*>     instances;
      // !temporary

      virtual void accept(Visitor& v);
  };
};

#endif /* !MSC_HH_ */
