#ifndef TEXT_DEFINITION_HH_
# define TEXT_DEFINITION_HH_

# include "msc/types.hh"

# include "msc/gen-visitor.hh"
# include "msc/statement.hh"
# include "msc/expression.hh"


namespace msc
{
  class TextDefinition : public Statement, public Expression
  {
   public:
      /// \name Ctor & Dtor
      /// \{
      TextDefinition(pString);

      virtual ~TextDefinition();
      /// \}

      /// \name Visitor entry point
      /// \{
      virtual void      accept(Visitor& v);
      /// \}

   private:
      pString   text_;
 };
} // namespace msc

#endif /* !TEXT_DEFINITION_HH_ */
