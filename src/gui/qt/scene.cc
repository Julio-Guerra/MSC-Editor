#include "gui/qt/scene.hh"

#include "msc/labelable.hh"
#include "view/qt/gmsc/all.hh"

using namespace gui;

Scene::Scene()
  : QGraphicsScene(),
    mode_ (MODE_SELECT),
    item_type_ (view::gmsc::Factory::ITEM_TYPE_NONE),
    item_ (NULL),
    message_ (NULL)
{
}

void Scene::set_mode(Mode mode)
{
  if ((mode_ == MODE_LABEL_EDITION) && (lineEdit_ != NULL))
  {
    QGraphicsSceneMouseEvent* mouseEvent = new QGraphicsSceneMouseEvent();

    mouseEvent->setButton(Qt::LeftButton);
    this->mousePressEvent(mouseEvent);
    delete mouseEvent;
  }

  mode_ = mode;
}

void Scene::set_type(view::gmsc::Factory::ItemType type)
{
  item_type_ = type;
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
          msc::Labelable*       labelable = dynamic_cast<msc::Labelable*> (items.at(i)->parentItem());

          if ((labelable != NULL) && (textInstance != NULL))
          {
            this->set_mode(MODE_LABEL_EDITION);
            labelable_ = labelable;
            lineEdit_ = new QLineEdit(labelable->label_get().name_get().c_str());
            lineEdit_->setParent(this->views().first());
            lineEdit_->move(mouseEvent->screenPos() - QPoint(310, 105));
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

void Scene::mousePressEvent(QGraphicsSceneMouseEvent*  mouseEvent)
{
  msc::pStatement   node = NULL;
  float             x = mouseEvent->scenePos().x();
  float             y = mouseEvent->scenePos().y();
  QString           q;

  if (mouseEvent->button() != Qt::LeftButton)
    return;

  switch (mode_)
  {
    case MODE_LABEL_EDITION:
      q = lineEdit_->text();
      labelable_->label_set(q.toStdString());
      lineEdit_->hide();
      delete lineEdit_;
      lineEdit_ = NULL;
      this->set_mode(MODE_SELECT);
      break;

    case MODE_ITEM_INSERTION:
      item_ = view::gmsc::Factory::instance().create_node(item_type_);
      node = dynamic_cast<msc::pStatement> (item_);
      if (node != NULL)
        statements_->push_back(node);
      item_->setPos(x, 5);
      this->addItem(item_);
      emit itemInserted(item_);
      break;

    case MODE_LINE_INSERTION:
      message_ = view::gmsc::Factory::instance().create_message();
      message_->setLine(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
      {
        QPen p = message_->pen();
        p.setWidth(2);
        message_->setPen(p);
      }
      this->addItem(message_);
      break;

    default:
      break;
  }

  QGraphicsScene::mousePressEvent(mouseEvent);
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
      if (message_ != NULL)
      {
        QLineF newLine(message_->line().p1(), mouseEvent->scenePos());
        message_->setLine(newLine);
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
      if (message_ == NULL)
        break;

      startItems = this->items(message_->line().p1());
      if (startItems.count() && (startItems.first() == message_))
        startItems.removeFirst();

      endItems = this->items(message_->line().p2());
      if (endItems.count() && (endItems.first() == message_))
        endItems.removeFirst();

      if ((startItems.count() > 0) && (endItems.count() > 0))
      {
        bool added = false;

        for (unsigned int i = 0; i < startItems.count(); ++i)
        {
          for (unsigned int j = 0; j < endItems.count(); ++j)
          {
            view::gmsc::Instance* startInstance = dynamic_cast<view::gmsc::Instance*> (startItems.at(i)->parentItem());
            view::gmsc::Instance* endInstance = dynamic_cast<view::gmsc::Instance*> (endItems.at(j)->parentItem());
            QGraphicsLineItem*    startInstanceLine = dynamic_cast<QGraphicsLineItem*> (startItems.at(i));
            QGraphicsLineItem*    endInstanceLine = dynamic_cast<QGraphicsLineItem*> (endItems.at(j));

            if ((startInstance != NULL) && (endInstance != NULL) &&
                (startInstanceLine != NULL) && (endInstanceLine != NULL) &&
                (startInstance != endInstance))
            {
              added = true;
              message_->from_set(startInstance);
              message_->from_pos_set(QPointF(-startInstance->x() + message_->line().p1().x(),
                                             -startInstance->y() + message_->line().p1().y()));
              message_->to_set(endInstance);
              message_->to_pos_set(QPointF(-endInstance->x() + message_->line().p2().x(),
                                           -endInstance->y() + message_->line().p2().y()));
              startInstance->events_get().push_back(msc::pEvent(message_));
              endInstance->events_get().push_back(msc::pEvent(message_));
              emit itemInserted(item_);
            }
          }
          if (!added)
            this->removeItem(message_);
        }
      }
      else
        this->removeItem(message_);

      message_ = NULL;
      break;

    default:
      break;
  }

  QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

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

    case MODE_SELECT:
      if (keyEvent->key() == Qt::Key_Delete)
      {
        view::Dtor dtor(this);

        foreach (QGraphicsItem* item, this->selectedItems())
        {
          msc::Ast*             ast = dynamic_cast<msc::Ast*> (item);
          view::gmsc::Instance* instance = dynamic_cast<view::gmsc::Instance*> (ast);

          ast->accept(dtor);

          if (instance)
          {
            std::vector<msc::pEvent>::iterator it;

            for (it = instance->events_get().begin(); it != instance->events_get().end(); ++it)
            {
              view::gmsc::Message* m = dynamic_cast<view::gmsc::Message*> (*it);

              if (m != NULL)
              {
                if (m->from_get() == instance)
                  m->to_get()->remove(m);
                if (m->to_get() == instance)
                  m->from_get()->remove(m);

                this->removeItem(m);
              }
            }
          }

          this->removeItem(item);
        }
      }
      break;

    default:
      break;
  }
}