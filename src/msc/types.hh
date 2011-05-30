#ifndef TYPES_HH_
# define TYPES_HH_

# include <boost/shared_ptr.hpp>

# include "msc/fwd.hh"
# include "misc/symbol.hh"

namespace msc
{
  typedef misc::Symbol                          String;

  typedef String                                Label;

  typedef String*                               pString;

  typedef Msc*                                  pMsc;

  typedef Statement*                            pStatement;

  typedef Instance*                             pInstance;

  typedef InstanceHead*                         pInstanceHead;

  typedef Identifier*                           pIdentifier;

  typedef Event*                                pEvent;

  typedef Message*                              pMessage;
}

#endif /* !TYPES_HH_ */
