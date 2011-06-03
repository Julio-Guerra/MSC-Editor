#ifndef GRAPH_VIEW_HH_
# define GRAPH_VIEW_HH_

# include <QtGui/QGraphicsView>
# include <QtGui/QResizeEvent>

namespace view
{
  class GraphView : public QGraphicsView
  {
    public:
      GraphView(QWidget*&);
  };
}

#endif /* !GRAPH_VIEW_HH_ */
