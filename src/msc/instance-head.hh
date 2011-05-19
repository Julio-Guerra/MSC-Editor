#ifndef INSTANCE_HEAD_HH_
# define INSTANCE_HEAD_HH_

# include "msc/types.hh"
# include "msc/event.hh"
# include "msc/gen-visitor.hh"
# include "msc/identifier.hh"

namespace msc
{
  class InstanceHead : public Event
  {
    public:
      /// \name Ctor & Dtor.
      /// \{
      InstanceHead(String*, Identifier*, bool, String*);

      virtual ~InstanceHead();
      /// \}

      /// \name Visitor entry point.
      /// \{
      virtual void accept(Visitor&);
      /// \}

//    private:
      /// Instance kind denominator.
      pString           kind_;

      /// Optional identifier.
      pIdentifier       identifier_;

      /// Is the instance decomposed ?
      bool              decomposed_;

      /// Optional substructure reference if decomposed.
      pString           substructure_;
  };
} // namespace msc

#endif /* !INSTANCE_HEAD_HH_ */
