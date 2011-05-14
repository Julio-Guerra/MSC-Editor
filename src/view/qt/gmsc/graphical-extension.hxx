#ifndef GRAPHICAL_EXTENSION_HXX_
# define GRAPHICAL_EXTENSION_HXX_

# include "graphical-extension.hh"
# include "draw.hh"

namespace gmsc
{
  template <class Decorated>
  GraphicalExtension<Decorated>::GraphicalExtension(Decorated* element)
    : element_ (element)
  {
  }

  template <class Decorated>
  void GraphicalExtension<Decorated>::accept(msc::Visitor& v)
  {
    v(*this);
  }
} // namespace gmsc

#endif /* !GRAPHICAL_EXTENSION_HXX_ */
