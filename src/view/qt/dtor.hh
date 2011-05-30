#ifndef DTOR_HH_
# define DTOR_HH_

# include <QtGui/QGraphicsScene>

# include "msc/default-visitor.hh"

namespace view
{
  class Dtor : public msc::DefaultVisitor
  {
    typedef msc::DefaultVisitor super_type;

    public:
      Dtor(QGraphicsScene*);

      void operator()(msc::Instance&);
      void operator()(msc::Message&);

    private:
      QGraphicsScene* scene_;
  };
}

#endif /* !DTOR_HH_ */
