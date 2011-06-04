#include "view/qt/graph-view.hh"
#include "view/qt/gmsc/all.hh"
#include "gui/qt/scene.hh"
#include "msc/basic-msc.hh"

using namespace view;

GraphView::GraphView(QWidget*& widget)
  : QGraphicsView(widget),
    message_no_ (0)
{
}

void GraphView::operator()(msc::BasicMsc& n)
{
  gui::Scene* s = dynamic_cast<gui::Scene*> (this->scene());

  super_type::operator()(n);
  s->statements_set(&(n.statements_get()));
}

void GraphView::operator()(msc::Instance& n)
{
  gmsc::Instance*       gn = dynamic_cast<gmsc::Instance*> (&n);

  super_type::operator()(n);

  scene()->addItem(gn);
}

void GraphView::operator()(msc::Message& n)
{
  gmsc::Message*       gn = dynamic_cast<gmsc::Message*> (&n);
  gmsc::Instance*      startInstance = dynamic_cast<gmsc::Instance*> (gn->from_get());
  gmsc::Instance*      endInstance = dynamic_cast<gmsc::Instance*> (gn->to_get());

  gn->from_pos_set(startInstance->startLine() + QPointF(0, message_no_));
  message_no_ += 15;
  gn->to_pos_set(endInstance->startLine() + QPointF(0, message_no_));
  message_no_ += 15;

  scene()->addItem(gn);
}
