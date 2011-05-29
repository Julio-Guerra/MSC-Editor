#ifndef LABELABLE_HH_
# define LABELABLE_HH_

# include "msc/types.hh"

namespace msc
{
  /** \brief Interface to factorize the label property.
   */
  class Labelable
  {
    public:
      /// \name Ctors
      /// \{
      Labelable(const Label&);
      /// \}

      /// Set the label property.
      virtual void        label_set(const Label&);

      /// Get the label property.
      const Label&        label_get() const;

    protected:
      Label               label_;
  };
} // namespace msc

#endif /* !LABELABLE_HH_ */
