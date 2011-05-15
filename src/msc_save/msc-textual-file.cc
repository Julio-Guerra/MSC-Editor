#include "msc/msc-textual-file.hh"

namespace msc
{
  MscTextualFile::MscTextualFile(TextualMscDocument* tmd)
    : mscs_(), tmd_(tmd)
  {
  }

  MscTextualFile::~MscTextualFile()
  {
    msc_vector::iterator i = mscs_.begin();
    for (; i != mscs_.end(); ++i)
      delete *i;
  }

  void MscTextualFile::push_back(Msc* msc)
  {
    mscs_.push_back(msc);
  }
} // namespace msc
