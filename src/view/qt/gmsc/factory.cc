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
  msc::Instance*      msc_instance = new msc::Instance(msc::String::fresh("Instance"));
  msc::InstanceHead*  instanceHead = new msc::InstanceHead(NULL, NULL, NULL);
  gmsc::Instance*     instance = new Instance(*msc_instance);

  instance->events_get().push_back(instanceHead);

  return instance;
}

Message* Factory::create_message()
{
  msc::Message* msc_message = new msc::Message(msc::String::fresh("message"), NULL, NULL);

  return (new Message(*msc_message));
}
