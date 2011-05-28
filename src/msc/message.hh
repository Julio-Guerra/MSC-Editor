#ifndef MESSAGE_HH_
# define MESSAGE_HH_

# include "msc/fwd.hh"
# include "msc/types.hh"

# include "msc/event.hh"
# include "msc/labelable.hh"
# include "msc/gen-visitor.hh"
# include "msc/instance.hh"

namespace msc
{
  class Message : public Event, public Labelable
  {
    public:
      /// \name Ctor & Dtor
      /// \{
      Message(const String& label, Instance*, Instance*);

      virtual ~Message();
      /// \}

      /// \name Accessors.
      /// \{
      void      from_set(Instance*);
      Instance& from_get() const;

      void      to_set(Instance*);
      Instance& to_get() const;
      /// \}

      /// \name Visitor entry point.
      /// \{
      virtual void accept(Visitor&);
      /// \}

//    private:
      /// This message is sent from an Instance.
      pInstance         from_;

      /// This message is sent to an Instance.
      pInstance         to_;
  };
}

# include "msc/message.hxx"

#endif /* !MESSAGE_HH_ */
