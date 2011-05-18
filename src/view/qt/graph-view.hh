#ifndef GRAPH_VIEW_HH_
# define GRAPH_VIEW_HH_

# include <QtGui/QGraphicsView>

# include "msc/all.hh"

namespace view
{
  class GraphView : public QGraphicsView, public msc::Visitor
  {
    public:
      GraphView(QWidget*&);

      virtual void operator()(msc::Msc&);
      virtual void operator()(msc::Instance&);
      virtual void operator()(msc::Message&);

    private:

  };
}

#endif /* !GRAPH_VIEW_HH_ */
