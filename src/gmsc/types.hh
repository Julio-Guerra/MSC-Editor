#ifndef TYPES_HH_
# define TYPES_HH_

# include "msc/fwd.hh"
# include "gmsc/graphical-extension.hh"

namespace gmsc
{
  typedef GrahicalExtension<msc::MscElement>            GMscElement;
  typedef GrahicalExtension<msc::EventArea>             GEventArea;
  typedef GrahicalExtension<msc::Instance>              GInstance;
  typedef GrahicalExtension<msc::MscMessage>            GMscMessage;
  typedef GrahicalExtension<msc::Msc>                   GMsc;
  typedef GrahicalExtension<msc::BasicMsc>              GBasicMsc;
  typedef GrahicalExtension<msc::Event>                 GEvent;
  typedef GrahicalExtension<msc::IncompleteMessage>     GIncompleteMessage;
  typedef GrahicalExtension<msc::StrictOrderArea>       GStrictOrderArea;
  typedef GrahicalExtension<msc::CoregionArea>          GCoregionArea;
  typedef GrahicalExtension<msc::CompleteMessage>       GCompleteMessage;
  typedef GrahicalExtension<msc::StrictEvent>           GStrictEvent;
  typedef GrahicalExtension<msc::CoregionEvent>         GCoregionEvent;
  typedef GrahicalExtension<msc::CoregionEventRelation> GCoregionEventRelation;
}

#endif /* !TYPES_HH_ */
