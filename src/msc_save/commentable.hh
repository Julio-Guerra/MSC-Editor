#ifndef COMMENTABLE_HH_
# define COMMENTABLE_HH_

# include <set>
# include "msc/comment.hh"

namespace msc
{
  class Commentable
  {
    public:
      typedef std::set<Comment*> Comments;

      void              comments_insert(Comment*);
      Comments&         comments_get() const;

    private:
      Comments  comments_;
  };
} // namespace msc

# include "msc/commentable.hxx"

#endif /* !COMMENTABLE_HH_ */
