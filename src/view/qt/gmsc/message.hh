#ifndef VIEW_GMSC_MESSAGE_HH_
# define VIEW_GMSC_MESSAGE_HH_

# include <QtGui/QPixmap>
# include <QtGui/QPainter>
# include <QtGui/QGraphicsLineItem>

# include "msc/message.hh"
# include "view/qt/gmsc/instance.hh"

namespace view
{
  namespace gmsc
  {
    class Message : public msc::Message, public QGraphicsLineItem
    {
      public:
        Message(const msc::Message&);
        virtual ~Message();

        // QT helper methods
        QPixmap& to_image();

        void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
        void label_set(const msc::Label&);

        //TODO: Remove this
        Instance*               from_;
        Instance*               to_;
        QPointF                 from_pos_;
        QPointF                 to_pos_;
      private:
        QGraphicsTextItem*      textItem_;
        QGraphicsRectItem*      rectItem_;
        QGraphicsPolygonItem*   extremity_;
    };
  }
}

#endif /* VIEW_GMSC_MESSAGE_HH_*/

