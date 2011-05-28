#ifndef SCENE_HH_
# define SCENE_HH_

# include <QtGui/QGraphicsView>
# include <QtGui/QGraphicsScene>
# include <QtGui/QGraphicsSceneMouseEvent>
# include <QtGui/QKeyEvent>
# include <QtGui/QLineEdit>

#include "view/qt/gmsc/fwd.hh"
#include "view/qt/gmsc/factory.hh"

namespace gui
{
  class Scene : public QGraphicsScene
  {
    Q_OBJECT

    public:
      enum Mode
      {
        MODE_SELECT = 0,
        MODE_ITEM_INSERTION,
        MODE_LINE_INSERTION,
        MODE_LABEL_EDITION,
      };

      Scene();

      void set_mode(Mode);
      void set_type(view::gmsc::Factory::ItemType);

    signals:
     void itemInserted(QGraphicsPolygonItem *item);

    private:
      Mode                          mode_;
      view::gmsc::Factory::ItemType item_type_;
      QGraphicsPolygonItem*         item_;
      QGraphicsLineItem*            line_;
      QLineEdit*                    lineEdit_;
      view::gmsc::Instance*         instanceEdit_;

      void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
      void mousePressEvent(QGraphicsSceneMouseEvent*);
      void mouseMoveEvent(QGraphicsSceneMouseEvent*);
      void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
      void keyPressEvent(QKeyEvent*);
  };
}

#endif	/* !SCENE_HH_ */

