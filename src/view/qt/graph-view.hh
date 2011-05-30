#ifndef GRAPH_VIEW_HH_
# define GRAPH_VIEW_HH_

# include <QtGui/QGraphicsView>
# include <QtGui/QResizeEvent>

# include "msc/default-visitor.hh"

namespace view
{
  class GraphView : public QGraphicsView, public msc::DefaultVisitor
  {
    public:
      GraphView(QWidget*&);
  };
}

#endif /* !GRAPH_VIEW_HH_ */
