#ifndef MISC_SYMBOL_HXX
# define MISC_SYMBOL_HXX

# include "misc/symbol.hh"

namespace misc
{
  inline const std::string& Symbol::name_get() const
  {
    return *obj_;
  }

  inline Symbol& Symbol::operator=(const Symbol& rhs)
  {
    if (this != &rhs)
      obj_ = rhs.obj_;

    return *this;
  }

  inline bool Symbol::operator==(const Symbol& rhs) const
  {
    return obj_ == rhs.obj_;
  }

  inline bool Symbol::operator!=(const Symbol& rhs) const
  {
    return obj_ != rhs.obj_;
  }

  inline std::ostream& operator<<(std::ostream& ostr, const Symbol& the)
  {
    return ostr << the.object_get ();
  }
}

#endif // !MISC_SYMBOL_HXX
