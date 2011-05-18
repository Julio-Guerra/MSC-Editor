#ifndef GRAPHICAL_EXTENSION_HXX_
# define GRAPHICAL_EXTENSION_HXX_

# include "view/qt/gmsc/graphical-extension.hh"

namespace view
{
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
} // namespace view

#endif /* !GRAPHICAL_EXTENSION_HXX_ */
