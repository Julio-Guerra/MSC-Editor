#ifndef EVENT_HH_
# define EVENT_HH_

# include "msc/msc-element.hh"
# include "msc/msc-message.hh"
# include "msc/event.hh"
# include "msc/gen-visitor.hh"

namespace msc
{
  class Event : public MscElement
  {
    public:
      virtual void accept(Visitor&);

    private:
      Event*            original_;

      MscMessage*       message_;
  };
} // namespace msc

#endif /* !EVENT_HH_ */
