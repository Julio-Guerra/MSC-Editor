#include "msc/instance.hh"
#include "msc/helper.hh"

namespace msc
{
  Instance::Instance()
  {
  }

  Instance::Instance(const Label&                       label,
                     const std::vector<Event*>&         events)
    : Labelable (label), events_ ()
  {
    msc::pv_to_spv(events, events_);
  }

  Instance::~Instance()
  {
  }

  void Instance::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
