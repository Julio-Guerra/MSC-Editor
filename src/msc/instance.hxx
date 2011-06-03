#ifndef MSC_INSTANCE_HXX_
# define MSC_INSTANCE_HXX_

# include "msc/instance.hh"
# include "msc/helper.hh"

namespace msc
{
  inline void Instance::events_set(const std::vector<Event*>& events)
  {
    //msc::pv_to_spv(events, events_);
    events_ = events;
  }

  inline std::vector<pEvent>& Instance::events_get()
  {
    return events_;
  }

  inline const InstanceHead&       Instance::head_get() const
  {
    return *head_;
  }

  inline void                      Instance::head_set(InstanceHead* head)
  {
    head_ = head;
  }
} // namespace msc

#endif /* !MSC_INSTANCE_HXX_ */
