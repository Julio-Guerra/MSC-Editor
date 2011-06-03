#include "msc/document.hh"

namespace msc
{
  Document::Document(DocumentHead*                              head,
                     const std::vector<MessageSequenceChart*>&  mscs)
    : head_ (head), mscs_ (mscs)
  {
  }

  Document::Document(DocumentHead*              head,
                     MessageSequenceChart*      msc)
    : head_ (head), mscs_ (1)
  {
    if (msc)
      mscs_.push_back(msc);
  }

  Document::~Document()
  {
  }

  void Document::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
