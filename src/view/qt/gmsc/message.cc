#include "view/qt/gmsc/message.hh"

#include <QtGui>
#include <math.h>

const qreal Pi = 3.14;

using namespace view::gmsc;

Message::Message(const msc::Message& message)
  : msc::Message(message)
{
  textItem_ = new QGraphicsTextItem(QString(message.label_get().name_get().c_str()), this);
  textItem_->setPos(this->boundingRect().center().x() - textItem_->boundingRect().width() / 2,
                    this->boundingRect().center().y() - textItem_->boundingRect().height() / 2);
  rectItem_ = new QGraphicsRectItem(textItem_->x(), textItem_->y(),
                                    textItem_->boundingRect().width(), textItem_->boundingRect().height(), this);
  rectItem_->setZValue(textItem_->zValue() - 1);
  extremity_ = new QGraphicsPolygonItem(this);
  {
    QPen   p = extremity_->pen();
    QBrush brush = extremity_->brush();

    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    extremity_->setBrush(brush);

    p.setColor(Qt::black);
    extremity_->setPen(p);
  }

  {
    QPen   p = rectItem_->pen();
    QBrush brush = rectItem_->brush();

    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    rectItem_->setBrush(brush);

    p.setColor(Qt::white);
    rectItem_->setPen(p);
  }

  this->setFlag(QGraphicsItem::ItemIsSelectable, true);
  this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}
#include <iostream>
Message::~Message()
{
  std::cout << "destructor message" << std::endl;
}

QPixmap& Message::to_image()
{
  QPixmap*  pixmap = new QPixmap(250, 250);

  pixmap->fill(Qt::transparent);

  {
    QPainter  painter(pixmap);

    painter.setPen(QPen(Qt::black, 3));
    painter.translate(0, 0);
    painter.drawLine(25, 80, 225, 180);
  }

  return (*pixmap);
}

void Message::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  QLineF    line = this->line();
  Instance* from = static_cast<Instance*> (this->from_get());
  Instance* to = static_cast<Instance*> (this->to_get());

  std::cerr << "painting " << this << std::endl;
  if (this->from_get() != NULL)
  {
    QPointF from_pt(from->x() + from_pos_.x(), from->y() + from_pos_.y());

    line.setP1(from_pt);
    this->setLine(line);
  }

  if (this->to_get() != NULL)
  {
    QPointF to_pt(to->x() + to_pos_.x(), to->y() + to_pos_.y());

    line.setP2(to_pt);
    this->setLine(line);
  }

  textItem_->setPos(this->boundingRect().center().x() - textItem_->boundingRect().width() / 2,
                    this->boundingRect().center().y() - textItem_->boundingRect().height() / 2);
  rectItem_->setRect(textItem_->x(), textItem_->y(), textItem_->boundingRect().width(), textItem_->boundingRect().height());

  if (this->line().dy() >= 0)
  {
    int       arrowSize = 14;
    double    angle = ::acos(this->line().dx() / this->line().length());
    QPointF   arrowP1;
    QPointF   arrowP2;
    QPolygonF p;

    angle = (Pi * 2) - angle;
    arrowP1 = this->line().p2() - QPointF(sin(angle + Pi / 3) * arrowSize, cos(angle + Pi / 3) * arrowSize);
    arrowP2 = this->line().p2() - QPointF(sin(angle + Pi - Pi / 3) * arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);
    p << this->line().p2() << arrowP1 << arrowP2;
    extremity_->setPolygon(p);
    extremity_->update(extremity_->boundingRect());
  }

  QGraphicsLineItem::paint(painter, option, widget);
}

void Message::label_set(const msc::Label& s)
{
  Labelable::label_set(s);
  textItem_->setPlainText(QString(s.name_get().c_str()));
}