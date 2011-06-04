#ifndef SCENE_HH_
# define SCENE_HH_

# include <QtGui/QGraphicsView>
# include <QtGui/QGraphicsScene>
# include <QtGui/QGraphicsSceneMouseEvent>
# include <QtGui/QKeyEvent>
# include <QtGui/QLineEdit>

# include "msc/fwd.hh"
# include "view/qt/gmsc/fwd.hh"
# include "view/qt/gmsc/factory.hh"
# include "view/qt/dtor.hh"

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
      inline msc::Ast*  root_get() const { return root_; }
      inline void       root_set(msc::Ast* ast) { root_ = ast; }

    signals:
     void itemInserted(QGraphicsPolygonItem *item);

    private:
      Mode                          mode_;
      view::gmsc::Factory::ItemType item_type_;
      QGraphicsPolygonItem*         item_;
      QLineEdit*                    lineEdit_;
      view::gmsc::Message*          message_;
      msc::Labelable*               labelable_;
      msc::Ast*                     root_;

      void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);
      void mousePressEvent(QGraphicsSceneMouseEvent*);
      void mouseMoveEvent(QGraphicsSceneMouseEvent*);
      void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
      void keyPressEvent(QKeyEvent*);
  };
}

#endif	/* !SCENE_HH_ */

