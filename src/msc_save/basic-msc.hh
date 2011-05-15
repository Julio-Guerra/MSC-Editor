#ifndef BASIC_MSC_HH_
# define BASIC_MSC_HH_

# include <list>
# include "msc/instance.hh"
# include "msc/msc.hh"

namespace msc
{
  class BasicMsc : public Msc
  {
    public:
      virtual void              accept(Visitor&);

      // void                      add_instance(Instance&);

      // bool                      remove_instances(const Label&);

      // const InstanceList&       instances_get() const;

    private:
      std::list<Instance*>      instances_;
  };
};

#endif /* !BASIC_MSC_HH_ */
