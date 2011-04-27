#ifndef PAR_EXPRESSION_HH_
# define PAR_EXPRESSION_HH_

# include "msc/ast.hh"
# include "msc/gen-visitor.hh"

namespace msc
{
  class ParExpression : public Ast
  {
    public:
      /** \name Ctor & Dtor.
       * \{ */
      virtual ~ParExpression();
      /** \} */

      virtual void      accept(Visitor&);

      /** \Push a new MscExpression pointer in the Msc vector.
       */
      void              push_back(MscExpression*);

    protected:
      typedef std::vector<MscExpression*> msc_expression_vector;

      /** Vector of MscExpression pointers owned by the class.
       */
      msc_expression_vector     msc_expressions_;
  };
} // namespace msc

#endif /* !PAR_EXPRESSION_HH_ */
