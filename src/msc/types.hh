#ifndef TYPES_HH_
# define TYPES_HH_

# include <string>
# include <boost/shared_ptr.hpp>

# include "msc/fwd.hh"
# include "misc/symbol.hh"

namespace msc
{
  typedef misc::Symbol                          String;

  typedef String                                Label;

  typedef boost::shared_ptr<String>             pString;

  typedef boost::shared_ptr<Msc>                pMsc;

  typedef boost::shared_ptr<Statement>          pStatement;

  typedef boost::shared_ptr<Instance>           pInstance;

  typedef boost::shared_ptr<InstanceHead>       pInstanceHead;

  typedef boost::shared_ptr<Identifier>         pIdentifier;

  typedef boost::shared_ptr<Event>              pEvent;

  typedef boost::shared_ptr<Message>            pMessage;
}

#endif /* !TYPES_HH_ */
