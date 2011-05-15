#ifndef STRICT_EVENT_HH_
# define STRICT_EVENT_HH_

# include "msc/event.hh"
# include "msc/strict-order-area.hh"

namespace msc
{
  class StrictEvent : public Event
  {
    public:
      virtual void accept(Visitor&);

    private:
      StrictEvent*      successor_;

      StrictEvent*      predecessor_;

      StrictOrderArea*  area_;
  };
} // namespace msc

#endif /* !STRICT_EVENT_HH_ */
