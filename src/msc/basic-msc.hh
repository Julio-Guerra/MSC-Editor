#ifndef MSC_BASIC_MSC_HH_
# define MSC_BASIC_MSC_HH_

# include <vector>

# include "msc/types.hh"
# include "msc/msc.hh"

namespace msc
{
  class BasicMsc : public Msc
  {
    public:
      /// \name Ctor & Dtor.
      /// \{
      BasicMsc(const std::vector<Statement*>& events);

      virtual ~BasicMsc();
      /// \}

      /// \name Accessors.
      /// \{
      std::vector<pStatement>&  statements_get();
      void                      statements_set(const std::vector<Statement*>&);
      /// \}

      /// \name Visitor entry point.
      /// \{
      virtual void      accept(Visitor&);
      /// \}

    private:
      /// Vector of MscStatements' shared pointers.
      std::vector<pStatement>        statements_;
  };
}

# include "msc/basic-msc.hxx"

#endif /* !MSC_BASIC_MSC_HH_ */
