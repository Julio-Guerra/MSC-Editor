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
      /// \name Ctor & Dtor.
      /// \{
      Identifier(String*, String*);

      virtual ~Identifier();
      /// \}

      /// \name Getters & Setters.
      /// \{
      pString           qualifier_get();
      void              qualifier_set(String*);

      pString           name_get();
      void              name_set(String*);
      /// \}

      /// \name Visitor entry point.
      /// \{
      virtual void      accept(Visitor&);
      /// \}

    private:
      /// Optional identifier qualifier.
      pString   qualifier_;

      /// Identifier Name.
      pString   name_;
  };
} // namespace msc

# include "msc/identifier.hxx"

#endif /* !IDENTIFIER_HH_ */
