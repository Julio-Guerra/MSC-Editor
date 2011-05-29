#ifndef MSC_IDENTIFIER_HXX_
# define MSC_IDENTIFIER_HXX_

# include "msc/identifier.hh"

namespace msc
{
  inline const pString  Identifier::qualifier_get()
  {
    return qualifier_;
  }

  inline void           Identifier::qualifier_set(String* qualifier)
  {
    qualifier_.reset(qualifier);
  }


  inline const pString  Identifier::name_get()
  {
    return name_;
  }

  inline void           Identifier::name_set(String* name)
  {
    name_.reset(name);
  }
} // namespace msc

#endif /* !IDENTIFIER_HXX_ */
