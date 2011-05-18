#ifndef INSTANCE_HH
# define	INSTANCE_HH

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

        QPixmap& to_image();

        void label_set(const QString&);

        // TO REMOVE
        QGraphicsTextItem* t_;

      private:
        QPolygonF polygon_;
    };
  }
}

#endif	/* INSTANCE_HH */

