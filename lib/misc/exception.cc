#include "misc/exception.hh"

namespace misc
{
  Exception::Exception(const char* message)
    : message_ (message)
  {
  }

  Exception::~Exception() throw ()
  {
  }

  const char* Exception::what() const throw()
  {
    return message_.c_str();
  }
} // namespace misc

