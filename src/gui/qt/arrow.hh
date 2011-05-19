#ifndef ARROW_H
# define ARROW_H

# include <QGraphicsLineItem>

# include "view/qt/gmsc/instance.hh"

class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;

class Arrow : public QGraphicsLineItem
{
public:
   enum { Type = UserType + 4 };

   Arrow(view::gmsc::Instance* startItem, view::gmsc::Instance* endItem,
     QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

   int type() const
       { return Type; }
   QRectF boundingRect() const;
   QPainterPath shape() const;
   void setColor(const QColor &color)
       { myColor = color; }
   view::gmsc::Instance* startItem() const
       { return myStartItem; }
   view::gmsc::Instance* endItem() const
       { return myEndItem; }

public slots:
   void updatePosition();

protected:
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
              QWidget *widget = 0);

private:
   view::gmsc::Instance* myStartItem;
   view::gmsc::Instance* myEndItem;
   QColor myColor;
   QPolygonF arrowHead;
};

#endif

