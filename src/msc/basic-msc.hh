#ifndef BASIC_MSC_HH_
# define BASIC_MSC_HH_

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
      BasicMsc(const std::vector<Statement*>&);

      virtual ~BasicMsc();
      /// \}

      /// \name Visitor entry point.
      /// \{
      virtual void      accept(Visitor&);
      /// \}

//    private:
      /// Vector of MscStatements' shared pointers.
      std::vector<pStatement>        statements_;
  };
}

#endif /* !BASIC_MSC_HH_ */
