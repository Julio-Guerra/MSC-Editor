#ifndef DEFAULT_VISITOR_HH_
# define DEFAULT_VISITOR_HH_

# include "msc/gen-visitor.hh"
# include "msc/fwd.hh"

namespace msc
{
  class DefaultVisitor : public Visitor
  {
    public:
      virtual void operator()(MessageSequenceChart&);
      virtual void operator()(BasicMsc&);
      virtual void operator()(Instance&);
      virtual void operator()(TextDefinition&);
      virtual void operator()(InstanceHead&);
      virtual void operator()(Identifier&);
      virtual void operator()(Message&);
  };
} // namespace msc

#endif /* !DEFAULT_VISITOR_HH_ */
