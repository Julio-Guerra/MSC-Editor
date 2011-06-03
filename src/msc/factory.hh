#ifndef MSC_FACTORY_HH_
# define MSC_FACTORY_HH_

# include <map>

# include "msc/all.hh"

namespace msc
{
  /** \brief Define singleton Factory class.
   *
   * Factory of msc nodes. Used by the parser and recommended
   * for the front-end to ligthen the ast creation.
   */
  class Factory
  {
    public:
      /// Unique instance getter.
      static Factory& instance();

      /** AST node creators.
       * \{ */
      /// Well formed MSC Document, i.e. with its header.
      Document* make_Document(DocumentHead*, MessageSequenceChart*);

      /// Non-standard MSC Document where the header is missing.
      Document* make_Document(const std::vector<MessageSequenceChart*>&);

      /// MSC Document header
      DocumentHead*     make_DocumentHead(String*, Identifier*);

      MessageSequenceChart*
      make_MessageSequenceChart(const String&,
                                MessageSequenceChart::virtuality_enum,
                                Msc*);

      Message* make_Message(const String&, Instance*, Instance*);

      /// Instance "forward declaration".
      Instance* make_Instance(const String&);

      /// MSC 92 - Instance definition.
      Instance* make_Instance(const String&,
                              InstanceHead*,
                              std::vector<Event*>&);

      /// > MSC 92 - Instance definition.
      Instance* make_Instance(const String&,
                              const std::vector<Event*>&);


      Identifier* make_Identifier(String*, String*);
      /** \} */

      /** Ctor & Dtor.
       * \{ */
    private:
      typedef std::map<String, Message*>        messages_map;

      typedef std::map<String, Instance*>       instances_map;

      Factory();

      virtual ~Factory();
      /** \} */

      /// Map of message names and their instances.
      /// Messages are common to several instances so we need
      /// to be able to get them to build the AST.
      messages_map                              messages_;

      /// Map of Instance names and their instances.
      /// Same as above, we need to give an Instance's instance to some
      /// nodes' constructors.
      instances_map                             instances_;
  };
} // namespace msc

#endif /* !MSC_FACTORY_HH_ */
