#ifndef GRAPHICAL_EXTENSION_HH_
# define GRAPHICAL_EXTENSION_HH_

# include "msc/gen-visitor.hh"

class Draw;

namespace view
{
    namespace gmsc
    {
      /** \brief Wrap a MscElement from the back-end with additional properties
       * required by a graphical rending.
       *
       * Using the decorator design pattern allows us to extend a class without
       * changing its interface.
       */
      template <class Decorated>
      class GraphicalExtension : public Decorated
      {
        public:
          GraphicalExtension(Decorated* element);

          virtual void accept(msc::Visitor&);

        private:
          Decorated* element_;

          /* FIXME: add graphical functionalities */
      };
    } // namespace gmsc
}// namespace view

# include "view/qt/gmsc/graphical-extension.hxx"

#endif /* !GRAPHICAL_EXTENSION_HH_ */
