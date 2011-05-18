#ifndef HELPER_HH_
# define HELPER_HH_

# include <vector>
# include <boost/shared_ptr.hpp>

namespace msc
{
  /// \brief Fill the shared_ptr vector with pointers from the vector of
  ///        pointers.
  template <class T>
  void pv_to_spv(const std::vector<T*>&,
                 std::vector<boost::shared_ptr<T> >&);
} // namespace msc

# include "msc/helper.hxx"

#endif /* !HELPER_HH_ */
