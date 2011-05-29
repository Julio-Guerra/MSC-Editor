#ifndef MSC_INSTANCE_HH_
# define MSC_INSTANCE_HH_

# include <vector>

# include "msc/statement.hh"
# include "msc/labelable.hh"
# include "msc/gen-visitor.hh"
# include "msc/event.hh"
# include "msc/instance-head.hh"

namespace msc
{
  class Instance : public Statement, public Labelable
  {
    public:
      /// \name Ctor & Dtor.
      // \{
      Instance(const String&);

      Instance(const String&,
               const std::vector<Event*>&);

      virtual ~Instance();
      /// \}

      /// \name Accessors.
      /// \{
      void                      events_set(const std::vector<Event*>&);
      std::vector<pEvent>&      events_get();
      /// \}

      /// \name Visitor entry point.
      /// \{
      virtual void accept(Visitor&);
      /// \}

    private:
      /// Vector of events ordered by declaration order.
      std::vector<pEvent>       events_;
  };
} // namespace msc

# include "msc/instance.hxx"

#endif /* !MSC_INSTANCE_HH_ */
