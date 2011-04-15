#include "msc/coregion-event-relation.hh"

namespace msc
{
  CoregionEventRelation::CoregionEventRelation(CoregionEvent* predecessor,
                                               CoregionEvent* successor)
    : successor_ (successor), predecessor_ (predecessor)
  {
  }

  void CoregionEventRelation::accept(Visitor& v)
  {
    v(*this);
  }

}
