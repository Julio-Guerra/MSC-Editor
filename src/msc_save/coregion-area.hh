#ifndef COREGION_AREA_HH_
# define COREGION_AREA_HH_

# include <vector>
# include <set>
# include "msc/event-area.hh"
# include "msc/gen-visitor.hh"
# include "msc/fwd.hh"


class CoregionEvent;
namespace msc
{
  class CoregionArea : public EventArea
  {
    public:
      virtual void accept(Visitor&);

    private:
      std::vector<CoregionEvent*>       minimal_events_;

      std::vector<CoregionEvent*>       maximal_events_;

      std::set<CoregionEvent*>          events_;
  };
}

#endif /* !COREGION_AREA_HH_ */
