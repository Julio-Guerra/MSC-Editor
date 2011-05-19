#ifndef FACTORY_HH_
# define	FACTORY_HH_

# include <QtGui/QGraphicsPolygonItem>

# include "view/qt/gmsc/fwd.hh"
# include "gui/qt/scene.hh"

namespace view
{
  namespace gmsc
  {
    class Factory
    {
      public:
        // Singleton method
        static Factory& instance();

        // Helper methods to create gmsc nodes
        QGraphicsPolygonItem* create_node(gui::Scene::ItemType);

        gmsc::Instance* create_instance();

      private:
        Factory();
    };
  }
}

#endif	/* !FACTORY_HH_ */

