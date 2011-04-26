#include "msc/comment.hh"

namespace msc
{
  Comment::Comment(const std::wstring& comment)
    : comment_(comment)
  {
  }

  void Comment::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
