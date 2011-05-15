#ifndef HIGH_MSC_NODE_HH_
# define HIGH_MSC_NODE_HH_

# include "msc/msc-element.hh"
# include "msc/gen-visitor.hh"
# include "msc/fwd.hh"

namespace msc
{
  class HighMscNode : public MscElement
  {
    private:
      void accept(Visitor&);

    private:
      HighMsc*  owner_;
  };
}

#endif /* !HIGH_MSC_NODE_HH_ */
