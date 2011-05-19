#ifndef MESSAGE_HH_
# define MESSAGE_HH_

# include "msc/fwd.hh"

# include "msc/event.hh"
# include "msc/labelable.hh"
# include "msc/gen-visitor.hh"

namespace msc
{
  class Message : public Event, public Labelable
  {
    public:
      typedef enum
      {
        IN = 0,
        OUT
      } direction_enum;

      /// \name Ctor & Dtor
      /// \{
      Message(direction_enum, String*);

      virtual ~Message();
      /// \}

      /// \name Visitor entry point.
      /// \{
      virtual void accept(Visitor&);
      /// \}

//    private:
      direction_enum    direction_;

      pString           instance_;
  };
}

#endif /* !MESSAGE_HH_ */
