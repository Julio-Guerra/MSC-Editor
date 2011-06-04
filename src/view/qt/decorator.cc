#include "view/qt/decorator.hh"

#include "msc/all.hh"
#include "view/qt/gmsc/all.hh"
#include "view/qt/gmsc/factory.hh"

using namespace view;

Decorator::Decorator(QGraphicsScene* scene)
  : scene_ (scene),
    result_ (NULL)
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

  this->recurseList(node.events_get(), decoratedEvents_);

  result_ = instance;
}

void Decorator::operator()(msc::Message& node)
{
  gmsc::Message* message = new gmsc::Message(node);

  result_ = message;
}