#include "parse/exception.hh"

namespace parse
{
  Exception::Exception(const char* message)
    : misc::Exception (message)
  {
  }
} // namespace Exception
