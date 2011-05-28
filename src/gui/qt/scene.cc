#include "gui/qt/scene.hh"

#include "view/qt/gmsc/instance.hh"

using namespace gui;

Scene::Scene()
  : QGraphicsScene(0, 0, 500, 500),
    mode_ (MODE_SELECT),
    item_type_ (view::gmsc::Factory::ITEM_TYPE_NONE),
    item_ (NULL),
    line_ (NULL)
{
}

void Scene::set_mode(Mode mode)
{
  mode_ = mode;
}

void Scene::set_type(view::gmsc::Factory::ItemType type)
{
  item_type_ = type;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent*  mouseEvent)
{
  float   x = mouseEvent->scenePos().x();
  float   y = mouseEvent->scenePos().y();
  QString q;

  if (mouseEvent->button() != Qt::LeftButton)
    return;

  switch (mode_)
  {
    case MODE_LABEL_EDITION:
      q = lineEdit_->text();
      instanceEdit_->label_set(q);
      lineEdit_->hide();
      delete lineEdit_;
      lineEdit_ = NULL;
      this->set_mode(MODE_SELECT);
      break;

    case MODE_ITEM_INSERTION:
      item_ = view::gmsc::Factory::instance().create_node(item_type_);
      item_->setPos(x, 5);
      this->addItem(item_);
      emit itemInserted(item_);
      break;

    case MODE_LINE_INSERTION:
      line_ = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                          mouseEvent->scenePos()));
      {
        QPen p = line_->pen();
        p.setWidth(2);
        line_->setPen(p);
      }
      this->addItem(line_);
      break;

    default:
      break;
  }

  QGraphicsScene::mousePressEvent(mouseEvent);
}

void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
  QList<QGraphicsItem *> items;

  switch (mode_)
  {
    case MODE_SELECT:
      items = this->items(mouseEvent->scenePos());
      if (items.count() != 0)
      {
        for (unsigned int i = 0; i < items.count(); ++i)
        {
          QGraphicsTextItem*    textInstance = dynamic_cast<QGraphicsTextItem*> (items.at(i));
          view::gmsc::Instance* instance = dynamic_cast<view::gmsc::Instance*> (items.at(i)->parentItem());

          if (instance)
          {
            this->set_mode(MODE_LABEL_EDITION);
            instanceEdit_ = instance;
            lineEdit_ = new QLineEdit(instance->label_get().c_str());
            lineEdit_->setParent(this->views().first());
            lineEdit_->setMinimumSize(instance->boundingRect().width(), instance->boundingRect().height());
            lineEdit_->move(instance->x() + 130, instance->y() + 5);
            lineEdit_->setFocus();
            lineEdit_->show();
          }
        }
      }
      break;

    default:
      break;
  }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent*  mouseEvent)
{
  QList<QGraphicsItem *> items;

  this->views().first()->setCursor(QCursor(Qt::ArrowCursor));
  switch (mode_)
  {
    case MODE_LINE_INSERTION:
      items = this->items(mouseEvent->scenePos());
      if (items.count() != 0)
      {
        for (unsigned int i = 0; i < items.count(); ++i)
        {
          QGraphicsLineItem*    instanceLine = dynamic_cast<QGraphicsLineItem*> (items.at(i));
          view::gmsc::Instance* instance = dynamic_cast<view::gmsc::Instance*> (items.at(i)->parentItem());

          if (instanceLine && instance)
            this->views().first()->setCursor(QCursor(Qt::CrossCursor));
        }
      }
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

      if ((startItems.count() > 0) && (endItems.count() > 0) && (startItems.first() != endItems.first()))
      {
        QGraphicsLineItem* startInstance = dynamic_cast<QGraphicsLineItem*> (startItems.first());
        QGraphicsLineItem* endInstance = dynamic_cast<QGraphicsLineItem*> (endItems.first());

        if ((startInstance == NULL) || (endInstance == NULL))
          this->removeItem(line_);
        else
          emit itemInserted(item_);
      }
      else
        this->removeItem(line_);

      line_ = NULL;
      break;

    default:
      break;
  }

  QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
#include <iostream>
void Scene::keyPressEvent(QKeyEvent* keyEvent)
{
  switch (mode_)
  {
    case MODE_LABEL_EDITION:
      if ((keyEvent->key() == Qt::Key_Return) || (keyEvent->key() == Qt::Key_Enter))
      {
        QGraphicsSceneMouseEvent* mouseEvent = new QGraphicsSceneMouseEvent();

        mouseEvent->setButton(Qt::LeftButton);
        this->mousePressEvent(mouseEvent);
        delete mouseEvent;
      }
      break;

    default:
      break;
  }
}