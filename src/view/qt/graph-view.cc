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
  scene()->addItem(gn);
}

void GraphView::operator()(msc::Message& n)
{
  gmsc::Message*       gn = dynamic_cast<gmsc::Message*> (&n);
  scene()->addItem(gn);
}
