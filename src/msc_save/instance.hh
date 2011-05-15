#ifndef INSTANCE_HH_
# define INSTANCE_HH_

# include "msc/msc-element.hh"
# include "msc/basic-msc.hh"
# include "msc/event-area.hh"
# include "msc/labelable.hh"
# include "msc/fwd.hh"

class EventArea;
namespace msc
{
  class Instance : public MscElement, public Labelable
  {
    public:
      virtual void accept(Visitor&);

    //   EInstanceAxisForm   form_get() const;

    //   void                first_set(const EventArea&);
    //   const EventArea&    first_get() const;

    //   void                last_set(const EventArea&);
    //   const EventArea&    last_get() const;

    //   void                bmsc_set(BasicMsc*);
    //   BasicMsc*           bmsc_get() const;

    private:
      Label             kind_;

      EventArea*        first_;

      EventArea*        last_;

      BasicMsc*         bmsc_;
  };
} // namespace msc

#endif /* !INSTANCE_HH_ */
