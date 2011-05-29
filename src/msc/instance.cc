#include "msc/instance.hh"

namespace msc
{
  Instance::Instance(const String&      label)
    : Labelable(label)
  {
  }

  Instance::Instance(const String&                      label,
                     const std::vector<Event*>&         events)
    : Labelable(label), events_()
  {
    events_set(events);
  }

  Instance::~Instance()
  {
  }

  void Instance::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
