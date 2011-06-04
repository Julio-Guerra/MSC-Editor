#include "view/qt/decorator.hh"

#include "msc/all.hh"
#include "view/qt/gmsc/all.hh"
#include "view/qt/gmsc/factory.hh"

using namespace view;

Decorator::Decorator()
  : result_ (0),
    instance_x (20)
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

  this->recurseList(instance->events_get(), decoratedEvents_);

  result_ = instance;
}

void Decorator::operator()(msc::Message& node)
{
  gmsc::Message* message = new gmsc::Message(node);

  result_ = message;
}

void Decorator::operator()(msc::Document& n)
{
  super_type::operator()(n);
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
