#include "view/qt/gmsc/factory.hh"

using namespace view::gmsc;


Factory::Factory()
{
}

Factory& Factory::instance()
{
  static Factory instance_;

  return instance_;
}

QGraphicsPolygonItem* Factory::create_node(gui::Scene::ItemType item_type){
  QGraphicsPolygonItem* node = NULL;
  
  switch (item_type)
  {
    case gui::Scene::ITEM_TYPE_BASIC_MSC:
      break;
      
    case gui::Scene::ITEM_TYPE_INSTANCE:
      node = this->create_instance();
      break;
      
    default:
      break;
  }
  
  return node;
}
       
Instance* Factory::create_instance()
{
  msc::Instance*  msc_instance = new msc::Instance("");
  
  return (new Instance(*msc_instance));
}

