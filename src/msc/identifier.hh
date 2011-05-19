#ifndef IDENTIFIER_HH_
# define IDENTIFIER_HH_

# include "msc/types.hh"
# include "msc/ast.hh"
# include "msc/gen-visitor.hh"

namespace msc
{
  class Identifier : public Ast
  {
    public:
      /// \name Visitor entry point.
      /// \{
      Identifier(String*, String*);

      virtual ~Identifier();
      /// \}

      /// \name Visitor entry point.
      /// \{
      virtual void accept(Visitor&);
      /// \}

    private:
      /// Optional identifier qualifier.
      pString   qualifier_;

      /// Identifier Name.
      pString   name_;
  };
} // namespace msc

#endif /* !IDENTIFIER_HH_ */
