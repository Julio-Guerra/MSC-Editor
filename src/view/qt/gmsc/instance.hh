#ifndef VIEW_GMSC_INSTANCE_HH_
# define	VIEW_GMSC_INSTANCE_HH_

# include <QtGui/QPainter>
# include <QtGui/QLabel>
# include <QtGui/QGraphicsItem>
# include <QtGui/QGraphicsTextItem>
# include <QtGui/QGraphicsScene>
 #include <QString>

# include "msc/instance.hh"

namespace view
{
  namespace gmsc
  {
    class Instance : public msc::Instance, public QGraphicsPolygonItem
    {
      public:
        Instance (const msc::Instance&);
        virtual ~Instance();

        void label_set(const msc::Label&);

        // QT helper methods
        QPixmap& to_image();

      private:
        QPolygonF           polygon_;
        QGraphicsLineItem*  lineItem_;
        QGraphicsRectItem*  rectItem_;
        QGraphicsTextItem*  textItem_;
    };
  }
}

#endif	/* VIEW_GMSC_INSTANCE_HH_ */

