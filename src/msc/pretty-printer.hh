#ifndef MSC_PRETTY_PRINTER_HH_
# define MSC_PRETTY_PRINTER_HH_

# include <ostream>

# include "msc/default-visitor.hh"
# include "msc/fwd.hh"

namespace msc
{
  /// \brief AST pretty-printer.
  /// Translate the AST into its textual representation.
  class PrettyPrinter : public DefaultVisitor
  {
    public:
      typedef DefaultVisitor super_type;

      using super_type::operator();

      /// \name Ctor & Dtor.
      /// \{
      PrettyPrinter(std::ostream&);
      virtual ~PrettyPrinter();
      /// \}

      /// \name Visitor methods.
      /// \{
      virtual void operator()(Document&);
      virtual void operator()(DocumentHead&);
      virtual void operator()(MessageSequenceChart&);
      virtual void operator()(Instance&);
      virtual void operator()(InstanceHead&);
      virtual void operator()(Identifier&);
      virtual void operator()(Message&);
      /// \}

    private:
      /// Output stream.
      std::ostream&     ostr_;

      /// Instance beeing visited.
      /// See operator()(Message&) implementation to understand
      /// why we needed this variable.
      Instance*         current_instance_;
  };
} // namespace msc

#endif /* !MSC_PRETTY_PRINTER_HH_ */
