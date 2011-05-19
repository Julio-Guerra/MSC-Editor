#include "msc/default-visitor.hh"
#include "msc/all.hh"
#include "msc/types.hh"

namespace msc
{
  void DefaultVisitor::operator()(BasicMsc& bmsc)
  {
    std::vector<pStatement>::iterator i;
    std::vector<pStatement>& v = bmsc.statements_;

    for (i = v.begin(); i != v.end(); ++i)
      (*i)->accept(*this);
  }

  void DefaultVisitor::operator()(Instance& instance)
  {
    std::vector<pEvent>::iterator i;
    std::vector<pEvent>& v = instance.events_;

    for (i = v.begin(); i != v.end(); ++i)
      (*i)->accept(*this);
  }

  void DefaultVisitor::operator()(TextDefinition& td)
  {
  }

  void DefaultVisitor::operator()(InstanceHead& ih)
  {
    ih.identifier_->accept(*this);
  }

  void DefaultVisitor::operator()(Identifier& id)
  {
  }

  void DefaultVisitor::operator()(Message& msg)
  {
  }

  void DefaultVisitor::operator()(MessageSequenceChart& msc)
  {
    msc.msc_->accept(*this);
  }
} // namespace msc
