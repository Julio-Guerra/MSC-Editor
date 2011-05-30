#include "msc/pretty-printer.hh"
#include "msc/all.hh"

namespace msc
{
  PrettyPrinter::PrettyPrinter(std::ostream& o)
    : ostr_ (o), current_instance_ (0)
  {
  }

  PrettyPrinter::~PrettyPrinter()
  {
  }

  void PrettyPrinter::operator()(MessageSequenceChart&  n)
  {
    ostr_ << "msc " << n.label_get() << ";" << std::endl;
    super_type::operator()(n);
    ostr_ << "endmsc;" << std::endl;
  }

  void PrettyPrinter::operator()(Instance&      n)
  {
    current_instance_ = &n;

    ostr_ << n.label_get() << ": ";
    super_type::operator()(n);
    ostr_ << n.label_get() << "endinstance;" << std::endl;

    current_instance_ = 0;
  }

  void PrettyPrinter::operator()(InstanceHead&  n)
  {
    ostr_ << "instance";

    if (n.kind_get() != 0)
      ostr_ << " " << n.kind_get();

    if (n.identifier_get() != 0)
    {
      ostr_ << " ";
      super_type::operator()(n);
    }

    if (n.substructure_get() != 0)
      ostr_ << " " << n.substructure_get();

    ostr_ << ";" << std::endl;
  }

  void PrettyPrinter::operator()(Identifier&    n)
  {
    if (n.qualifier_get() != 0)
      ostr_ << n.qualifier_get() << " ";

    ostr_ << n.name_get();

    super_type::operator()(n);
  }

  void PrettyPrinter::operator()(Message&       n)
  {
    bool out = (n.from_get() == current_instance_);
    const pInstance instance = out ? n.to_get() : n.from_get();

    ostr_ << (out ? "out " : "in ")
          << n.label_get() << (out ? " to " : " from ")
          << instance->label_get()
          << ";" << std::endl;

    super_type::operator()(n);
  }
} // namespace msc

