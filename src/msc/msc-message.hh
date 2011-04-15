#ifndef MSC_MESSAGE_HH_
# define MSC_MESSAGE_HH_

# include "msc/msc-element.hh"
# include "msc/gen-visitor.hh"
# include "msc/labelable.hh"

namespace msc
{
  class MscMessage : public MscElement, public Labelable
  {
    public:
      virtual void accept(Visitor&);
  };
}

#endif /* !MSC_MESSAGE_HH_ */
