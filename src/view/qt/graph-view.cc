#include "view/qt/graph-view.hh"
#include "view/qt/gmsc/all.hh"

using namespace view;

GraphView::GraphView(QWidget*& widget)
  : QGraphicsView(widget)
{
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

  gn->from_pos_set(QPointF(-startInstance->x() + gn->line().p1().x(),
                                 -startInstance->y() + gn->line().p1().y()));
  gn->to_pos_set(QPointF(-endInstance->x() + gn->line().p2().x(),
                               -endInstance->y() + gn->line().p2().y()));

  scene()->addItem(gn);
}
