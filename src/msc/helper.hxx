#ifndef MSC_HELPER_HXX_
# define MSC_HELPER_HXX_

# include "msc/helper.hh"

namespace msc
{
  template <class T>
  void pv_to_spv(const std::vector<T*>&                 pv,
                 std::vector<boost::shared_ptr<T> >&    spv)
  {
    typename std::vector<T*>::const_iterator i;

    for (i = pv.begin(); i != pv.end(); ++i)
      spv.push_back(boost::shared_ptr<T>(*i));
  }
} // namespace msc

#endif /* !MSC_HELPER_HXX_ */
