#ifndef MSC_BASIC_MSC_HXX_
# define MSC_BASIC_MSC_HXX_

# include "msc/basic-msc.hh"
# include "msc/helper.hh"
# include "msc/instance.hh"

namespace msc
{
  std::vector<pStatement>& BasicMsc::statements_get()
  {
    return statements_;
  }

  void BasicMsc::statements_set(const std::vector<Statement*>& v)
  {
    msc::pv_to_spv(v, statements_);
  }
} // namespace

#endif /* !MSC_BASIC_MSC_HXX_ */
