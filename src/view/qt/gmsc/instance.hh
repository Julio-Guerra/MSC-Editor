#ifndef INSTANCE_HH
# define	INSTANCE_HH

# include <QtGui/QPainter>
# include <QtGui/QGraphicsItem>

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

      private:
        QPolygonF polygon_;
    };
  }
}

#endif	/* INSTANCE_HH */

