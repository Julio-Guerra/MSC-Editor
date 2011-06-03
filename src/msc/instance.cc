#include "msc/instance.hh"
#include <iostream>
namespace msc
{
  Instance::Instance(const String&      label)
    : Labelable(label), head_ (0), events_ ()
  {
  }

  Instance::Instance(const String&                      label,
                     InstanceHead*                      head,
                     const std::vector<Event*>&         events)
    : Labelable(label), head_ (head), events_()
  {
    events_set(events);
  }

  Instance::~Instance()
  {
  }

  void Instance::remove(Event* e)
  {
    std::vector<pEvent>::iterator   it;
    std::vector<pEvent>::iterator   toDeleteIt;
    bool                            found = false;

    for (it = events_.begin(); it != events_.end(); ++it)
    {
      if (*it == e)
      {
        found = true;
        toDeleteIt = it;
      }
    }

    events_.erase(toDeleteIt);
  }

  void Instance::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
