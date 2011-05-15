#ifndef MSC_TEXTUAL_FILE_HH_
# define MSC_TEXTUAL_FILE_HH_

# include <vector>
# include "msc/ast.hh"
# include "msc/gen-visitor.hh"
# include "msc/msc.hh"
# include "msc/textual-msc-document.hh"

namespace msc
{
  class MscTextualFile : public Ast
  {
    public:
      /** \name Ctor & Dtor.
       * \{ */
      MscTextualFile(TextualMscDocument*);

      virtual ~MscTextualFile();
      /** \} */

      virtual void      accept(Visitor&);

      /** \Push a new Msc pointer in the Msc vector.
       */
      void              push_back(Msc*);

    protected:
      typedef std::vector<Msc*> msc_vector;

      /** Msc pointers vector.
       * These pointers are owned by the class.
       */
      msc_vector                mscs_;

      /** Pointer to a TextualMscDocument owned by the class.
       */
      TextualMscDocument*       tmd_;
  };
} // msc

#endif /* !MSC_TEXTUAL_FILE_HH_ */
