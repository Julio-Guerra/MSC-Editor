#ifndef DECORATOR_HH_
# define DECORATOR_HH_

# include <QtGui/QGraphicsScene>
# include <map>
# include <vector>

# include "msc/types.hh"
# include "msc/default-visitor.hh"
# include "view/qt/gmsc/fwd.hh"

namespace view
{
  class Decorator : public msc::DefaultVisitor
  {
    public:
      typedef msc::DefaultVisitor       super_type;

      using super_type::operator();

      Decorator();

      virtual void operator()(msc::Document&);
      virtual void operator()(msc::DocumentHead&);
      virtual void operator()(msc::MessageSequenceChart&);
      virtual void operator()(msc::InstanceHead&);
      virtual void operator()(msc::Identifier&);
      virtual void operator()(msc::BasicMsc&);
      virtual void operator()(msc::Instance&);
      virtual void operator()(msc::Message&);

      template<typename T>
      T* recurse(T&);
      template<typename T>
      void recurseList(std::vector<T>&, std::map<T, T>&);

    private:
      msc::Ast*                                         result_;
      std::map<msc::pStatement, msc::pStatement>        decoratedStatements_;
      std::map<msc::pEvent, msc::pEvent>                decoratedEvents_;
      unsigned int                                      instance_x;
  };
}

# include "view/qt/decorator.hxx"

#endif /* !DECORATOR_HH_ */
