#ifndef TEXTUAL_MSC_DOCUMENT_HH_
# define TEXTUAL_MSC_DOCUMENT_HH_

# include "msc/ast.hh"
# include "msc/gen-visitor.hh"

namespace msc
{
  class TextualMscDocument : public Ast
  {
    public:
      /** \name Ctor & Dtor.
       * \{ */
      TextualMscDocument(documentHead*, TextualDefiningPart* /*fixme*/);

      virtual ~TextualMscDocument();
      /** \} */

      virtual void      accept(Visitor&);

    protected:

  };
} // namespace msc

#endif /* !TEXTUAL_MSC_DOCUMENT_HH_ */
