#ifndef MSC_INSTANCE_HEAD_HH_
# define MSC_INSTANCE_HEAD_HH_

# include "msc/types.hh"
# include "msc/event.hh"
# include "msc/gen-visitor.hh"
# include "msc/identifier.hh"

namespace msc
{
  class InstanceHead : public Event
  {
    public:
      /// \name Ctor & Dtor.
      /// \{
      InstanceHead(String*, Identifier*, String*);

      virtual ~InstanceHead();
      /// \}

      /// \name Accessors.
      /// \{
      pString           kind_get() const;
      void              kind_set(String*);

      pIdentifier       identifier_get() const;
      void              identifier_set(Identifier*);

      pString           substructure_get() const;
      /// Set the substructure and decomposed if not null.
      void              substructure_set(String*);

      /// Decomposed boolean is true if substructure is not null.
      bool              is_decomposed() const;
      /// \}

      /// \name Visitor entry point.
      /// \{
      virtual void accept(Visitor&);
      /// \}

    private:
      /// Optional Instance kind denominator.
      pString           kind_;

      /// Optional identifier.
      pIdentifier       identifier_;

      /// Optional substructure pointer if decomposed.
      pString           substructure_;
  };
} // namespace msc

# include "msc/instance-head.hxx"

#endif /* !MSC_INSTANCE_HEAD_HH_ */
