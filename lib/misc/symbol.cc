#include <sstream>
#include <boost/lexical_cast.hpp>

#include "misc/symbol.hh"

namespace misc
{
  Symbol::Symbol (const std::string& s)
    : Unique<std::string>(s)
  {
  }

  Symbol::Symbol(const char* s)
    : Unique<std::string>(std::string(s))
  {
  }

  Symbol::~Symbol ()
  {
  }

  Symbol::string_size_type Symbol::string_map_size()
  {
    return object_map_size();
  }

  /// Create a new unique symbol, forged from \a s.
  Symbol Symbol::fresh(const Symbol& s)
  {
    static unsigned int count_ = 0;

    return Symbol(s.object_get () + "_"
                  + boost::lexical_cast<std::string>(count_++));
  }
  /** \} */

} // namespace misc
