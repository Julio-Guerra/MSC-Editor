#ifndef TYPES_HH_
# define TYPES_HH_

# include "msc/all.hh"
# include "view/qt/gmsc/instance.hh"

// Remove this
# include "view/qt/gmsc/graphical-extension.hh"

namespace view
{
    namespace gmsc
    {
      typedef GraphicalExtension<msc::Instance>     GInstance;
      typedef GraphicalExtension<msc::Msc>          GMsc;
      typedef GraphicalExtension<msc::Message>      GMessage;
    }
}

#endif /* !TYPES_HH_ */
