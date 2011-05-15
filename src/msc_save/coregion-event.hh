#ifndef COREGION_EVENT_HH_
# define COREGION_EVENT_HH_

# include "msc/event.hh"
# include "msc/coregion-area.hh"
# include "msc/coregion-event-relation.hh"

namespace msc
{
  class CoregionEvent : public Event
  {
    public:
      virtual void accept(Visitor&);

    private:
      CoregionArea*                             area_;

      std::vector<CoregionEventRelation*>       successors_;

      std::vector<CoregionEventRelation*>       predecessors_;
  };
} // namespace msc

#endif /* !COREGION_EVENT_HH_ */
