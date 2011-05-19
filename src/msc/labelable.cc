#include "msc/labelable.hh"

namespace msc
{
  Labelable::Labelable()
    : label_ ()
  {
  }

  Labelable::Labelable(const Label& label)
    : label_ (label)
  {
  }

  void          Labelable::label_set(const Label& label)
  {
    label_ = label;
  }

  const Label&  Labelable::label_get() const
  {
    return label_;
  }
}
