#ifndef INSTANCE_HH_
# define INSTANCE_HH_

# include <vector>
# include "msc/ast.hh"
# include "msc/gen-visitor.hh"
# include "msc/message.hh"

class EventArea;
namespace msc
{
  class Instance : public Ast, public Labelable
  {
    public:
      Instance();
      Instance(const Instance&);
      virtual ~Instance();

      // temporary
      // 1) Use Labelable to name the Instance.
      // 2) Message: from -> to
      //    from is this Instance
      std::vector<Message*>      messages;
      // !temporary

      virtual void accept(Visitor&);
  };
} // namespace msc

#endif /* !INSTANCE_HH_ */
