#ifndef COMMENT_HXX_
# define COMMENT_HXX_

# include "msc/comment.hh"

namespace msc
{
  inline void Comment::comment_set(const std::wstring& comment)
  {
    comment_ = comment;
  }

  inline const std::wstring& Comment::comment_get() const
  {
    return (comment_);
  }
} // namespace msc

#endif /* !COMMENT_HXX_ */
