#ifndef TYPES_HH_
# define TYPES_HH_

# include <boost/shared_ptr.hpp>

# include "msc/fwd.hh"
# include "misc/symbol.hh"

namespace msc
{
  // These typedefs were created to switch to a smart pointer
  // class transparent enough to be considered as a normal pointer
  // by the rest of the code.

  // TODO : replace the pointers by "garbage collected" smart pointers.

  typedef misc::Symbol                          String;

  typedef String                                Label;

  typedef String*                               pString;

  typedef MessageSequenceChart*                 pMessageSequenceChart;

  typedef Document*                             pDocument;

  typedef DocumentHead*                         pDocumentHead;

  typedef Msc*                                  pMsc;

  typedef Statement*                            pStatement;

  typedef Instance*                             pInstance;

  typedef InstanceHead*                         pInstanceHead;

  typedef Identifier*                           pIdentifier;

  typedef Event*                                pEvent;

  typedef Message*                              pMessage;
}

#endif /* !TYPES_HH_ */
