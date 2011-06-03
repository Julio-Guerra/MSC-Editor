#ifndef DOCUMENT_HXX_
# define DOCUMENT_HXX_

# include "msc/document.hh"

namespace msc
{
  inline pDocumentHead          Document::head_get() const
  {
    return head_;
  }

  inline Document::mscs_type&   Document::mscs_get()
  {
    return mscs_;
  }
}

#endif /* !DOCUMENT_HXX_ */
