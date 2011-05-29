#include "msc/basic-msc.hh"
#include "msc/helper.hh"

namespace msc
{
  BasicMsc::BasicMsc(const std::vector<Statement*>& v)
  {
    statements_set(v);
  }

  BasicMsc::~BasicMsc()
  {
  }

  void BasicMsc::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
