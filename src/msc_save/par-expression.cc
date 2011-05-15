#include "msc/par-expression.hh"

namespace msc
{
  ParExpression::~ParExpression()
  {
    msc_expression_vector::iterator i = msc_expressions_.begin();
    for (; i != msc_expressions_.end(); ++i)
      delete *i;
  }

  void ParExpression::accept(Visitor& v)
  {
    v(*this);
  }

  void ParExpression::push_back(MscExpression* me)
  {
    msc_expressions_.push_back(me);
  }
} // namespace msc
