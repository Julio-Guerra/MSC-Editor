#ifndef EVENT_AREA_HH_
# define EVENT_AREA_HH_

# include "msc/msc-element.hh"
# include "msc/instance.hh"
# include "msc/gen-visitor.hh"

namespace msc
{
  class EventArea : public MscElement
  {
    public:
      virtual void accept(Visitor&);

    private:
      EventArea*        previous_;

      EventArea*        next_;

      Instance*         instance_;
  };
}

#endif /* !EVENT_AREA_HH_ */
