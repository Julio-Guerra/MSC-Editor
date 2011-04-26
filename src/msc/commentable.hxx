#ifndef COMMENTABLE_HXX_
# define COMMENTABLE_HXX_

# include "msc/commentable.hh"

namespace msc
{
  inline void Commentable::comments_insert(Comment* c)
  {
    comments_.insert(c);

    // Insertion of duplicated comments will fail, we ignore it.
  }

  inline Commentable::Comments& Commentable::comments_get() const
  {
    return (comments_);
  }
} // namespace msc

#endif /* !COMMENTABLE_HXX_ */
