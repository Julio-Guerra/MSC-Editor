#ifndef LABELABLE_HH_
# define LABELABLE_HH_

# include <string>

namespace msc
{
  /** \brief Interface to factorize the label property.
   */
  class Labelable
  {
    public:
      typedef std::string Label;

      /// Set the label property.
      void                label_set(const Label&);

      /// Get the label property.
      const Label&        label_get() const;

    protected:
      Label               label_;
  };
} // namespace msc

#endif /* !LABELABLE_HH_ */
