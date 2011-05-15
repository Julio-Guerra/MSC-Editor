#ifndef COMMENT_HH_
# define COMMENT_HH_

# include <string>
# include "msc/msc-element.hh"
# include "msc/gen-visitor.hh"

namespace msc
{
  class Comment : public MscElement
  {
    public:
      Comment(const std::wstring& comment = L"");

      const std::wstring&       comment_get() const;
      void                      comment_set(const std::wstring&);

      virtual void              accept(Visitor&);

    private:
      std::wstring              comment_;
  };
} // namespace msc

# include "msc/comment.hxx"

#endif /* !COMMENT_HH_ */
