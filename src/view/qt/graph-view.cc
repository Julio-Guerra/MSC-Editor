#include "view/qt/graph-view.hh"
#include "view/qt/gmsc/all.hh"

using namespace view;

GraphView::GraphView(QWidget*& widget)
  : QGraphicsView(widget)
{
}

void GraphView::operator()(msc::Msc& node)
{
  //gmsc::GMsc& gnode = static_cast<gmsc::GMsc&> (node);

  //this->scene()->addItem();
}

void GraphView::operator()(msc::Instance& node)
{
  gmsc::Instance& gnode = static_cast<gmsc::Instance&> (node);

  this->scene()->addItem(&gnode);
  //accept(gnode.element_->last_);
}

void GraphView::operator()(msc::Message& node)
{
  //gmsc::GMessage& gnode = static_cast<gmsc::GMessage&> (node);

  //this->scene()->addItem();
}
