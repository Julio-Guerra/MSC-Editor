#include "instance.hh"

namespace msc
{
  Instance::Instance()
  {
  }

  Instance::Instance(const Instance& instance)
    : Labelable(instance), messages(std::vector<Message*> (instance.messages.size()))
  {
    std::vector<Message*>::const_iterator it;

    for (it = instance.messages.begin(); it != instance.messages.end(); ++it)
    {
      Message *m = new Message(**it);

      messages.push_back(m);
    }
  }

  Instance::~Instance()
  {
  }

  void Instance::accept(Visitor& v)
  {
    v(*this);
  }
} // namespace msc
