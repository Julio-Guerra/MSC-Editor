#ifndef INSTANCE_HH_
# define INSTANCE_HH_

# include <vector>

# include "msc/statement.hh"
# include "msc/labelable.hh"
# include "msc/gen-visitor.hh"
# include "msc/message.hh"


namespace msc
{
  class Instance : public Statement, public Labelable
  {
    public:
      /// \name Ctor & Dtor
      // \{
      Instance(const Label&/*,
               const std::vector<msc::Instance*>&*/);

      virtual ~Instance();
      /// \}

      /// \name Visitor entry point.
      /// \{
      virtual void accept(Visitor&);
      /// \}

    private:
      ///
      /// std::vector<>
  };
} // namespace msc

#endif /* !INSTANCE_HH_ */
