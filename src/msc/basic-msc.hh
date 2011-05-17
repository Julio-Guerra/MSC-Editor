#ifndef BASIC_MSC_HH_
# define BASIC_MSC_HH_

# include <vector>
# include "msc/ast.hh"


namespace msc
{
  class BasicMsc : public Ast
  {
    public:
      virtual void              accept(Visitor&);

      // void                      add_instance(Instance&);

      // bool                      remove_instances(const Label&);

      // const InstanceList&       instances_get() const;

    private:
//      std::vector<Instance*>      instances_;
  };
};

#endif /* !BASIC_MSC_HH_ */
