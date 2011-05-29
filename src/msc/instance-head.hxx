#ifndef MSC_INSTANCE_HEAD_HXX_
# define MSC_INSTANCE_HEAD_HXX_

# include "msc/instance-head.hh"

namespace msc
{
  inline const pString     InstanceHead::kind_get() const
  {
    return kind_;
  }

  inline void              InstanceHead::kind_set(String* kind)
  {
    kind_.reset(kind);
  }

  inline bool              InstanceHead::is_decomposed() const
  {
    return (substructure_ != 0);
  }

  inline const pString  InstanceHead::substructure_get() const
  {
    return substructure_;
  }

  inline void           InstanceHead::substructure_set(String* sub)
  {
    substructure_.reset(sub);
  }

  inline const pIdentifier      InstanceHead::identifier_get() const
  {
    return identifier_;
  }

  inline void                   InstanceHead::identifier_set(Identifier* id)
  {
    identifier_.reset(id);
  }
} // namespace msc

#endif /* !MSC_INSTANCE_HEAD_HXX_ */
