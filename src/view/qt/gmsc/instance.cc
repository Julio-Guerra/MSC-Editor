#include "view/qt/gmsc/instance.hh"

using namespace view::gmsc;

Instance::Instance(const msc::Instance& instance)
  : msc::Instance(instance),
    polygon_(QRectF(-10, -10, 100, 50))
{
  QString s(instance.label_get().c_str());
  QGraphicsTextItem t(s);
  
  this->setPolygon(polygon_);
  
  this->setFlag(QGraphicsItem::ItemIsMovable, true);
  this->setFlag(QGraphicsItem::ItemIsSelectable, true);
  this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

Instance::~Instance()
{
}
