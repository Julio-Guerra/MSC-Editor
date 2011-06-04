#ifndef GRAPH_VIEW_HH_
# define GRAPH_VIEW_HH_

# include <QtGui/QGraphicsView>
# include <QtGui/QResizeEvent>
# include "msc/default-visitor.hh"

namespace view
{
  class GraphView : public QGraphicsView, msc::DefaultVisitor
  {
    public:
      typedef msc::DefaultVisitor super_type;

      using msc::DefaultVisitor::operator();

      GraphView(QWidget*&);

      /// \name msc::DefaultVisitor interface.
      /// \{
      virtual void operator()(msc::Instance&);
      virtual void operator()(msc::Message&);
      /// \}
  };
}

#endif /* !GRAPH_VIEW_HH_ */
