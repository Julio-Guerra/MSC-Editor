#ifndef MSC_IDENTIFIER_HXX_
# define MSC_IDENTIFIER_HXX_

# include "msc/identifier.hh"

namespace msc
{
  inline pString  Identifier::qualifier_get()
  {
    return qualifier_;
  }

  inline void           Identifier::qualifier_set(String* qualifier)
  {
    qualifier_ = qualifier;
  }


  inline pString  Identifier::name_get()
  {
    return name_;
  }

  inline void           Identifier::name_set(String* name)
  {
    name_ = name;
  }
} // namespace msc

#endif /* !IDENTIFIER_HXX_ */
