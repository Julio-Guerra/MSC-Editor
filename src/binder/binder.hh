#ifndef BINDER_HH_
# define BINDER_HH_

# include "msc/default-visitor.hh"

namespace binder
{
  class Binder : public msc::DefaultVisitor
  {
    public:
      virtual void operator()(msc::BasicMsc&);
      virtual void operator()(msc::Instance&);
      virtual void operator()(msc::TextDefinition&);
      virtual void operator()(msc::InstanceHead&);
      virtual void operator()(msc::Identifier&);
      virtual void operator()(msc::Message&);
      virtual void operator()(msc::MessageSequenceChart&);

    protected:
      typedef DefaultVisitor    super;
  };
} // namespace binder

#endif /* !BINDER_HH_ */
