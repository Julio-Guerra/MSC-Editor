#ifndef PARSE_EXCEPTION_HH_
# define PARSE_EXCEPTION_HH_

# include "misc/exception.hh"

namespace parse
{
  class Exception : public misc::Exception
  {
    public:
      Exception(const char*);
  };
} // namespace parse

#endif /* !PARSE_EXCEPTION_HH_ */
