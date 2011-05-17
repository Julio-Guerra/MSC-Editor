#include "msc/basic-msc.hh"

namespace msc
{
  BasicMsc::BasicMsc(const std::vector<pStatement>& v)
    : statements_ (v)
  {
  }

  BasicMsc::~BasicMsc()
  {
  }

  void BasicMsc::accept(Visitor& v)
  {
    v(*this);
  }
}
