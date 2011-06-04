#include "view/qt/decorator.hh"

#include "msc/all.hh"
#include "view/qt/gmsc/all.hh"
#include "view/qt/gmsc/factory.hh"

using namespace view;

Decorator::Decorator()
  : result_ (0),
    instance_x (20),
    update_me ()
{
}

void Decorator::operator()(msc::BasicMsc& node)
{
  this->recurseList(node.statements_get(), decoratedStatements_);

  result_ = &node;
}

void Decorator::operator()(msc::Instance& node)
{
  gmsc::Instance* instance = new gmsc::Instance(node);
  instance->setPos(instance_x, 30);
  instance_x += 250;

  this->recurseList(node.events_get(), decoratedEvents_);

  result_ = instance;
}

void Decorator::operator()(msc::Message& node)
{
  gmsc::Message* message = new gmsc::Message(node);
  update_me.push_back(message);
  result_ = message;
}

void Decorator::operator()(msc::Document& n)
{
  super_type::operator()(n);

  std::list<gmsc::Message*>::iterator   i;
  for (i = update_me.begin(); i != update_me.end(); ++i)
  {
    std::map<msc::pStatement, msc::pStatement>::iterator from;
    std::map<msc::pStatement, msc::pStatement>::iterator to;
    from = decoratedStatements_.find((*i)->from_get());
    to = decoratedStatements_.find((*i)->to_get());

    if (from != decoratedStatements_.end())
      (*i)->from_set((msc::Instance*) from->second);

    if (to != decoratedStatements_.end())
      (*i)->to_set((msc::Instance*) to->second);
  }

  result_ = &n;
}

void Decorator::operator()(msc::DocumentHead& n)
{
  super_type::operator()(n);
  result_ = &n;
}

void Decorator::operator()(msc::MessageSequenceChart& n)
{
  super_type::operator()(n);
  result_ = &n;
}

void Decorator::operator()(msc::InstanceHead& n)
{
  super_type::operator()(n);
  result_ = &n;
}

void Decorator::operator()(msc::Identifier& n)
{
  super_type::operator()(n);
  result_ = &n;
}
