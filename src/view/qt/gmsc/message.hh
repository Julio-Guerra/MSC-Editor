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

        inline QPointF from_pos_get() const { return from_pos_; };
        inline void from_pos_set(QPointF p) { from_pos_ = p; };

        inline QPointF to_pos_get() const { return to_pos_; };
        inline void to_pos_set(QPointF p) { to_pos_ = p; }

      private:
        QPointF                 from_pos_;
        QPointF                 to_pos_;
        QGraphicsTextItem*      textItem_;
        QGraphicsRectItem*      rectItem_;
        QGraphicsPolygonItem*   extremity_;
    };
  }
}

#endif /* VIEW_GMSC_MESSAGE_HH_*/

