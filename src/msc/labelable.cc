#include "msc/labelable.hh"

namespace msc
{
  void            Labelable::label_set(const Label& label)
  {
    label_ = label;
  }

  const Labelable::Label&    Labelable::label_get() const
  {
    return label_;
  }
}
