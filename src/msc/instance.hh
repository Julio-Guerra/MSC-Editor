#ifndef INSTANCE_HH_
# define INSTANCE_HH_

# include <vector>

# include "msc/statement.hh"
# include "msc/labelable.hh"
# include "msc/gen-visitor.hh"
# include "msc/event.hh"

namespace msc
{
  class Instance : public Statement, public Labelable
  {
    public:
      /// \name Ctor & Dtor.
      // \{
      Instance();

      Instance(const String&,
               const std::vector<Event*>&);

      virtual ~Instance();
      /// \}

      /// \name Visitor entry point.
      /// \{
      virtual void accept(Visitor&);
      /// \}

//    private:
      ///
      std::vector<pEvent>    events_;
  };
} // namespace msc

#endif /* !INSTANCE_HH_ */
