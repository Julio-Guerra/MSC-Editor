#include "gui/qt/scene.hh"
#include "gui/qt/arrow.hh"

#include "view/qt/gmsc/factory.hh"

using namespace gui;

Scene::Scene()
  : QGraphicsScene(0, 0, 800, 800),
    mode_ (MODE_SELECT),
    item_type_ (ITEM_TYPE_NONE),
    item_ (NULL),
    line_ (NULL)
{
}

void Scene::set_mode(Mode mode)
{
  mode_ = mode;
}

void Scene::set_type(ItemType type)
{
  item_type_ = type;
}
#include <iostream>
void Scene::mousePressEvent(QGraphicsSceneMouseEvent*  mouseEvent)
{
  float   x = mouseEvent->scenePos().x();
  float   y = mouseEvent->scenePos().y();
  
  if (mouseEvent->button() != Qt::LeftButton)
    return;

  switch (mode_) {
    
    case MODE_ITEM_INSERTION:
      item_ = view::gmsc::Factory::instance().create_node(item_type_);
      item_->setPos(x, y);
      this->addItem(item_);
      emit itemInserted(item_);
      break;
      
    case MODE_LINE_INSERTION:
      line_ = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                          mouseEvent->scenePos()));
      addItem(line_);
      break;
      
    default:
      break;
  }
    
  QGraphicsScene::mousePressEvent(mouseEvent);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent*  mouseEvent)
{
  switch (mode_) {
    
    case MODE_LINE_INSERTION:
      if (line_ != NULL)
      {
        QLineF newLine(line_->line().p1(), mouseEvent->scenePos());
        line_->setLine(newLine);
      }
      break;
      
    default:
      QGraphicsScene::mouseMoveEvent(mouseEvent);
      break;
  }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent*  mouseEvent)
{
  QList<QGraphicsItem *> startItems;
  QList<QGraphicsItem *> endItems;

  switch (mode_) {
    
    case MODE_LINE_INSERTION:
      startItems = this->items(line_->line().p1());
      if (startItems.count() && (startItems.first() == line_))
        startItems.removeFirst();
      
      endItems = this->items(line_->line().p2());
      if (endItems.count() && (endItems.first() == line_))
        endItems.removeFirst();

      removeItem(line_);
      delete line_;
      
      if ((startItems.count() > 0) && (endItems.count() > 0) && (startItems.first() != endItems.first()))
      {
        view::gmsc::Instance* startInstance = dynamic_cast<view::gmsc::Instance*> (startItems.first());
        view::gmsc::Instance* endInstance = dynamic_cast<view::gmsc::Instance*> (endItems.first());
        
        if (startInstance == NULL)
        {
          QGraphicsItem* item = startItems.first();
          startInstance = dynamic_cast<view::gmsc::Instance*> (item->parentItem());
        }
        
        if (endInstance == NULL)
        {
          QGraphicsItem* item = endItems.first();
          endInstance = dynamic_cast<view::gmsc::Instance*> (item->parentItem());
        }
        
        if ((startInstance != NULL) && (endInstance != NULL))
        {
          //line_ = new QGraphicsLineItem();
          //QLineF line(startInstance->pos(), endInstance->pos());
          //line_->setLine(line);
          Arrow* arrow = new Arrow(startInstance, endInstance);
          
          arrow->setZValue(-1000.0);
          addItem(arrow);
          arrow->updatePosition();
        }
      }
      
      line_ = NULL;
      break;
      
    default:
      break;
  }

  QGraphicsScene::mouseReleaseEvent(mouseEvent);
}