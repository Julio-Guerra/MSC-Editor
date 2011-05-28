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
      Factory& instance();

      /** AST node creators.
       * \{ */
      MessageSequenceChart*
      make_MessageSequenceChart(String*,
                                MessageSequenceChart::virtuality_enum,
                                Msc*);

      Message* make_Message(String*, Instance*, Instance*);

      Instance* make_Instance(const String&,
                              const std::vector<Event*>&);

      /** \} */

      /** Ctor & Dtor.
       * \{ */
    private:
      typedef std::map<String, Message*>        messages_map;

      Factory();

      virtual ~Factory();
      /** \} */

      /// Map of message names and their instances.
      /// Messages are common to several instances so we need
      /// to be able to get to build the AST.
      messages_map                              messages_;
  };
} // namespace msc

#endif /* !MSC_FACTORY_HH_ */
