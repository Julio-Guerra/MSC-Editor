#ifndef STRICT_ORDER_AREA_HH_
# define STRICT_ORDER_AREA_HH_

# include "msc/event-area.hh"
# include "msc/gen-visitor.hh"

class StrictEvent;

namespace msc
{
  class StrictOrderArea : public EventArea
  {
    public:
      virtual void accept(Visitor&);

    private:
      StrictEvent*      first_;

      StrictEvent*      last_;
  };
} // namespace msc

#endif /* !STRICT_ORDER_AREA_HH_ */
