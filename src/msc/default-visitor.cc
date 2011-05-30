#include "msc/default-visitor.hh"
#include "msc/all.hh"
#include "msc/types.hh"

namespace msc
{
  void DefaultVisitor::operator()(BasicMsc& bmsc)
  {
    std::vector<pStatement>::iterator i;
    std::vector<pStatement>& v = bmsc.statements_get();

    for (i = v.begin(); i != v.end(); ++i)
      (*i)->accept(*this);
  }

  void DefaultVisitor::operator()(Instance& instance)
  {
    std::vector<pEvent>::iterator i;
    std::vector<pEvent>& v = instance.events_get();

    for (i = v.begin(); i != v.end(); ++i)
      (*i)->accept(*this);
  }

  void DefaultVisitor::operator()(InstanceHead& ih)
  {
    accept(ih.identifier_get());
  }

  void DefaultVisitor::operator()(Identifier& id)
  {
    (void) id;
  }

  void DefaultVisitor::operator()(Message& msg)
  {
    (void) msg;
  }

  void DefaultVisitor::operator()(MessageSequenceChart& msc)
  {
    msc.msc_get()->accept(*this);
  }
} // namespace msc
