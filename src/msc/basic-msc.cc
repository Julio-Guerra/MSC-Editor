#include "msc/basic-msc.hh"

#include "msc/helper.hh"

namespace msc
{
  BasicMsc::BasicMsc(const std::vector<Statement*>& v)
  {
//    msc::pv_to_spv<Statement*>(v, statements_);
    std::vector<Statement*>::const_iterator i;

    for (i = v.begin(); i != v.end(); ++i)
    {
//      pStatement ps(*i);
//      statements_.push_back();
    }

  }

  BasicMsc::~BasicMsc()
  {
  }

  void BasicMsc::accept(Visitor& v)
  {
    v(*this);
  }
}
