#include "msc/factory.hh"

namespace msc
{
  Factory::Factory()
    : messages_ ()
  {
  }

  Factory::~Factory()
  {
  }

  Factory& Factory::instance()
  {
    static Factory instance_;
    return instance_;
  }

  MessageSequenceChart*
  Factory::make_MessageSequenceChart(const String&      name,
                                     MessageSequenceChart::virtuality_enum v,
                                     Msc*               msc)
  {
    return new MessageSequenceChart(name, v, msc);
  }

  // TODO: if labels are null, get it from symbol::fresh(str)

  Message* Factory::make_Message(const String&  label,
                                 Instance*      from,
                                 Instance*      to)
  {
    messages_map::iterator      it = messages_.find(label);
    Message*                    message = 0;

    // e.g.:
    // instance i1;       (0)
    //   in m from i2;    (1)
    // endinstance;
    // instance i2;
    //   out m to i1;     (2)
    // endinstance;

    if (it == messages_.end())
    {
      // Message instance not created yet.
      // e.g. case (1) where we don't know in which Instance the message
      // is defined. The instance is partially declared.
      // Moreover, it is not possible to define in the parser at (0) that i1 is
      // the Instance source of Message m and the solution of defining the
      // message in two steps as in the language. To understand why we can't do
      // it in a single step, have a look at the grammar src/msc/Msc.g, rule
      // messageInput or messageOuput and you will notice that we can't know
      // where we come from in rule (0).

      message = new Message(label, from, to);
      messages_.insert(std::pair<String, Message*>(label, message));
    }
    else
    {
      // Message instance already created. Which means we are giving more
      // informations about the message. E.g. case (2) where the Message m is
      // fully declared, the destination is finally given.

      message = it->second;

      // One of the Message's argument is null. So we make sure not to
      // override information previously set.
      if (message->from_get())
        // assert(from == 0)
        message->to_set(to);
      else if (message->to_get())
        // assert(to == 0)
        message->from_set(from);

      // TODO: gestion d'erreur
    }

    return message;
  }


  Instance* Factory::make_Instance(const String&                label)
  {
    instances_map::iterator     it = instances_.find(label);

    if (it != instances_.end())
      return it->second;

    Instance* instance = new Instance(label);
    instances_.insert(std::pair<String, Instance*>(label, instance));

    return instance;
  }

  Instance* Factory::make_Instance(const String&                label,
                                   InstanceHead*                head,
                                   const std::vector<Event*>&   events)
  {
    instances_map::iterator     it = instances_.find(label);

    if (it != instances_.end())
    {
      it->second->events_set(events);
      return it->second;
    }

    Instance* instance = new Instance(label, head, events);
    instances_.insert(std::pair<String, Instance*>(label, instance));

    return instance;
  }

  Document*  Factory::make_Document(DocumentHead*               head,
                                    MessageSequenceChart*       msc)
  {
    Document::mscs_type v;
    v.push_back(msc);
    return new Document(head, v);
  }

  Document*
  Factory::make_Document(const std::vector<MessageSequenceChart*>& mscs)
  {
    Identifier* id = make_Identifier(0, new String(String::fresh("document")));
    return new Document(make_DocumentHead(0, id), mscs);
  }

  DocumentHead*
  Factory::make_DocumentHead(String* kind, Identifier* identifier)
  {
    return new DocumentHead(kind, identifier);
  }

  Identifier*   Factory::make_Identifier(String* qualifier, String* name)
  {
    return new msc::Identifier(qualifier, name);
  }
} // namespace msc

