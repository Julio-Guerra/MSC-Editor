#ifndef MSC_DOCUMENT_HEAD_HXX_
# define MSC_DOCUMENT_HEAD_HXX_

# include "msc/document-head.hh"

namespace msc
{
  inline pString
  DocumentHead::kind_get() const
  {
    return kind_;
  }

  inline pIdentifier
  DocumentHead::identifier_get() const
  {
    return identifier_;
  }

} // namespace msc

#endif /* !MSC_DOCUMENT_HEAD_HXX_ */
