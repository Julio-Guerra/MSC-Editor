#ifndef HIGH_MSC_HH_
# define HIGH_MSC_HH_

# include <set>
# include "msc/msc.hh"
# include "msc/gen-visitor.hh"
# include "msc/high-msc-node.hh"
# include "msc/start-node.hh"

namespace msc
{
  class HighMsc : public Msc
  {
    public:
      virtual void accept(Visitor&);

    private:
      StartNode*                start_;

      std::set<HighMscNode*>    nodes_;
  };
} // namespace msc

#endif /* !HIGH_MSC_HH_ */
