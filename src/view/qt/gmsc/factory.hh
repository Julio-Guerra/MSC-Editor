#ifndef FACTORY_HH_
# define	FACTORY_HH_

# include <QtGui/QGraphicsPolygonItem>

# include "view/qt/gmsc/fwd.hh"

namespace view
{
  namespace gmsc
  {
    class Factory
    {
      public:
        enum ItemType
        {
          ITEM_TYPE_NONE = 0,

          // MSC Element
          ITEM_TYPE_BASIC_MSC,
          ITEM_TYPE_INSTANCE,

          // Messages
          ITEM_TYPE_MESSAGE,
        };

        // Singleton method
        static Factory& instance();

        // Helper methods to create gmsc nodes
        QGraphicsPolygonItem* create_node(ItemType);

        gmsc::Instance* create_instance();
        gmsc::Message*  create_message();

      private:
        Factory();
    };
  }
}

#endif	/* !FACTORY_HH_ */
