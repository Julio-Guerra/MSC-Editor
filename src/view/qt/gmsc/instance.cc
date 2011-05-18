#include "view/qt/gmsc/instance.hh"

using namespace view::gmsc;

Instance::Instance(const msc::Instance& instance)
  : msc::Instance(instance),
    polygon_(QRectF(-10, -10, 100, 50))
{
  QString* s = new QString(instance.label_get().c_str());
  
  t_ = new QGraphicsTextItem(*s, this);
  
  this->setPolygon(polygon_);
  
  this->setFlag(QGraphicsItem::ItemIsMovable, true);
  this->setFlag(QGraphicsItem::ItemIsSelectable, true);
  this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

Instance::~Instance()
{
}

QPixmap& Instance::to_image()
{
  QPixmap*  pixmap = new QPixmap(250, 250);
  
  pixmap->fill(Qt::transparent);
  
  {
    QPainter  painter(pixmap);
    
    painter.setPen(QPen(Qt::black, 2));
    painter.translate(100, 100);
    painter.drawPolygon(polygon_);
  }
  
  return (*pixmap);
}

void Instance::label_set(const Label& l)
{
  Labelable::label_set(l);
  QString* s = new QString(label_get().c_str());
  t_->setPlainText(*s);
}