#ifndef MSC_BASIC_MSC_HXX_
# define MSC_BASIC_MSC_HXX_

# include "msc/basic-msc.hh"
# include "msc/helper.hh"
# include "msc/instance.hh"

namespace msc
{
  inline std::vector<pStatement>& BasicMsc::statements_get()
  {
    return statements_;
  }

  inline void BasicMsc::statements_set(const std::vector<Statement*>& v)
  {
    msc::pv_to_spv(v, statements_);
  }
} // namespace

#endif /* !MSC_BASIC_MSC_HXX_ */
