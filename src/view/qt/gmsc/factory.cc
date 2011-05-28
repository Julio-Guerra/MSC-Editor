#include "view/qt/gmsc/factory.hh"
#include "view/qt/gmsc/all.hh"

using namespace view::gmsc;


Factory::Factory()
{
}

Factory& Factory::instance()
{
  static Factory instance_;

  return instance_;
}

QGraphicsPolygonItem* Factory::create_node(ItemType item_type){
  QGraphicsPolygonItem* node = NULL;

  switch (item_type)
  {
    case ITEM_TYPE_BASIC_MSC:
      break;

    case ITEM_TYPE_INSTANCE:
      node = this->create_instance();
      break;

    default:
      break;
  }

  return node;
}

Instance* Factory::create_instance()
{
  msc::Instance*  msc_instance = new msc::Instance();

  msc_instance->label_set("Test");
  return (new Instance(*msc_instance));
}

