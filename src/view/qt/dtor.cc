#include "view/qt/dtor.hh"
#include "view/qt/gmsc/all.hh"

using namespace view;

Dtor::Dtor(QGraphicsScene* scene)
  : scene_ (scene)
{
}

void Dtor::operator()(msc::Instance& node)
{
  gmsc::Instance& gnode = static_cast<gmsc::Instance&> (node);

  super_type::operator()(gnode);

  this->scene_->removeItem(&gnode);
}

void Dtor::operator()(msc::Message& node)
{
  gmsc::Message& gnode = static_cast<gmsc::Message&> (node);

  this->scene_->removeItem(&gnode);
}
