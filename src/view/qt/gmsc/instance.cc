#include "view/qt/gmsc/instance.hh"

using namespace view::gmsc;

Instance::Instance(const msc::Instance& instance)
  : msc::Instance(instance)
{
  polygon_ << QPointF(0, 0) << QPointF(140, 0);
  polygon_ << QPointF(140, 30) << QPointF(0, 30);

  textItem_ = new QGraphicsTextItem(QString(instance.label_get().c_str()), this);

  lineItem_ = new QGraphicsLineItem(70, 30, 70, 500, this);
  QPen p = lineItem_->pen();
  p.setWidth(3);
  lineItem_->setPen(p);

  rectItem_ = new QGraphicsRectItem(0, 500, 140, 17, this);
  QBrush brush = rectItem_->brush();
  brush.setColor(Qt::black);
  brush.setStyle(Qt::SolidPattern);
  rectItem_->setBrush(brush);
  rectItem_->setPen(p);

  this->setPen(p);
  this->setPolygon(polygon_);
  this->setFlag(QGraphicsItem::ItemIsMovable, true);
  this->setFlag(QGraphicsItem::ItemIsSelectable, true);
  this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

  textItem_->setPos(this->boundingRect().center().x() - textItem_->boundingRect().width() / 2, textItem_->pos().y() - 25);
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
    painter.translate(55, 10);
    painter.drawPolygon(polygon_);
    painter.drawLine(lineItem_->line());
    painter.drawRect(rectItem_->rect());
  }

  return (*pixmap);
}

void Instance::label_set(const QString& l)
{
  Labelable::label_set(l.toStdString());
  textItem_->setPlainText(l);
  textItem_->setPos(this->boundingRect().center().x() - textItem_->boundingRect().width() / 2, textItem_->pos().y());
}
