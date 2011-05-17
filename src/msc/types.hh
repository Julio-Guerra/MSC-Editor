#ifndef TYPES_HH_
# define TYPES_HH_

# include <string>
# include <boost/shared_ptr.hpp>

# include "msc/fwd.hh"

namespace msc
{
  typedef std::string                           String;

  typedef String                                Label;

  typedef boost::shared_ptr<String>             pString;

  typedef boost::shared_ptr<Msc>                pMsc;

  typedef boost::shared_ptr<Statement>          pStatement;

  typedef boost::shared_ptr<TextDefinition>     pTextDefinition;
}

#endif /* !TYPES_HH_ */
