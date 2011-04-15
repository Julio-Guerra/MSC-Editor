#ifndef MSC_HH_
# define MSC_HH_

# include "msc/msc-element.hh"
# include "msc/labelable.hh"
# include "msc/gen-visitor.hh"

namespace msc
{
  class Msc: public MscElement, public Labelable
  {
    public:
      virtual void accept(Visitor& v);
  };
};

#endif /* !MSC_HH_ */
