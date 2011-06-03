#ifndef MSC_DOCUMENT_HH_
# define MSC_DOCUMENT_HH_

# include <vector>
# include "msc/types.hh"
# include "msc/ast.hh"

namespace msc
{
  /// Root node of a MSC.
  class Document : public Ast
  {
    public:
      typedef std::vector<pMessageSequenceChart>        mscs_type;

      /// \name Ctor & Dtor.
      /// \{
      Document(DocumentHead*, MessageSequenceChart*);
      Document(DocumentHead*, const std::vector<MessageSequenceChart*>&);

      virtual ~Document();
      /// \}

      /// \name Getters & Setters.
      /// \{
      pDocumentHead     head_get() const;

      mscs_type&        mscs_get();
      /// \}

      /// \name Visitor entry point.
      /// \{
      virtual void accept(Visitor&);
      /// \}

    private:
      pDocumentHead     head_;

      /// MSC 2000 and 96 compliant.
      /// Many MessageSequenceCharts is possible in MSC 2000.
      /// Only one MessageSequenceChart in MSC 96.
      mscs_type         mscs_;
  };
} // namespace msc

# include "msc/document.hxx"

#endif /* !MSC_DOCUMENT_HH_ */
