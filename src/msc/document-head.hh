#ifndef DOCUMENT_HEAD_HH_
# define DOCUMENT_HEAD_HH_

# include "msc/types.hh"
# include "msc/ast.hh"

namespace msc
{
  class DocumentHead : public Ast
  {
    public:
      /// \name Ctor & Dtor.
      /// \{
      DocumentHead(String*, Identifier*);
      virtual ~DocumentHead();
      /// \}

      /// \name Getters & Setters.
      /// \{
      pString           kind_get() const;

      pIdentifier       identifier_get() const;
      /// \}

      /// \name Visitor entry point.
      /// \{
      virtual void accept(Visitor&);
      /// \}

    private:
      pString           kind_;

      pIdentifier       identifier_;
  };
} // namespace msc

# include "msc/document-head.hxx"

#endif /* !DOCUMENT_HEAD_HH_ */
