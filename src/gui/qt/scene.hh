#ifndef SCENE_HH_
# define SCENE_HH_

# include <QtGui/QGraphicsScene>
# include <QtGui/QGraphicsSceneMouseEvent>

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
      };

      enum ItemType
      {
        ITEM_TYPE_NONE = 0,
        
        // MSC Element
        ITEM_TYPE_BASIC_MSC,
        ITEM_TYPE_INSTANCE,
        
        // Messages
        ITEM_TYPE_MESSAGE,
      };

      Scene();

      void set_mode(Mode);
      void set_type(ItemType);
      
    signals:
     void itemInserted(QGraphicsPolygonItem *item);
      
    private:
      Mode                  mode_;
      ItemType              item_type_;
      QGraphicsPolygonItem* item_;
      QGraphicsLineItem*    line_;

      void mousePressEvent(QGraphicsSceneMouseEvent*);
      void mouseMoveEvent(QGraphicsSceneMouseEvent*);
      void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
  };
}

#endif	/* !SCENE_HH_ */

