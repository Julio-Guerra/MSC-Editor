#ifndef COREGION_EVENT_RELATION_HH_
# define COREGION_EVENT_RELATION_HH_

# include "msc/msc-element.hh"
# include "msc/gen-visitor.hh"
# include "msc/fwd.hh"

class CoregionEvent;

namespace msc
{
  class CoregionEventRelation : public MscElement
  {
    public:
      CoregionEventRelation(CoregionEvent* predecessor,
                            CoregionEvent* successor);

      CoregionEvent*    successor_get() const;
      void              successor_set(CoregionEvent*);

      CoregionEvent*    predecessor_get() const;
      void              predecessor_set(CoregionEvent*);

      virtual void      accept(Visitor&);

    private:
      CoregionEvent*    successor_;

      CoregionEvent*    predecessor_;
  };
} // namespace msc

# include "msc/coregion-event-relation.hxx"

#endif /* !COREGION_EVENT_RELATION_HH_ */
