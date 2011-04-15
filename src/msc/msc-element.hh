#ifndef MSC_ELEMENT_HH_
# define MSC_ELEMENT_HH_

# include <string>
# include <map>
# include "msc/types.hh"
# include "msc/gen-visitor.hh"

namespace msc
{
  class MscElement
  {
    public:
      typedef std::map<std::string, void*> AttributeMap;

      enum mark_e
      {
        NONE,
        MARKED,
        ADDED,
        REMOVED
      };
      typedef mark_e mark_e;

      virtual void accept(Visitor&) = 0;

      /// Attributes' methods
      /// \{
      // bool is_attribute_set(const std::string&) const;

      // template <class T>
      // T& attribute_get(const std::string&, const T&);

      // template <class T>
      // T& attribute_get(const std::string&, const T&, bool&);

      // template <class T>
      // T& attribute_set(const std::string&, const T&);

      // template <class T>
      // T& attribute_remove(const std::string&);

      // std::set<std::string> attributes_names_get() const;
      /// \}

      // mark_e mark_get() const;

      // void mark_set(mark_e);

    private:
      AttributeMap      attributes_;

      mark_e            mark_;
  };
} // namespace msc

#endif /* !MSC_ELEMENT_HH_ */
