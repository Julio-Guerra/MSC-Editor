#ifndef COREGION_EVENT_RELATION_HXX_
# define COREGION_EVENT_RELATION_HXX_

# include "msc/coregion-event-relation.hh"

namespace msc
{
  inline CoregionEvent* CoregionEventRelation::predecessor_get() const
  {
    return predecessor_;
  }

  inline CoregionEvent* CoregionEventRelation::successor_get() const
  {
    return successor_;
  }

  inline void CoregionEventRelation::predecessor_set(CoregionEvent* pred)
  {
    predecessor_ = pred;
  }

  inline void CoregionEventRelation::successor_set(CoregionEvent* successor)
  {
    successor_ = successor;
  }
} // namespace msc

#endif /* !COREGION_EVENT_RELATION_HXX_ */
