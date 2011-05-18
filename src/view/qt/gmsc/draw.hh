#ifndef DRAW_HH_
# define DRAW_HH_

# include "gmsc/graphical-extension.hh"
# include "msc/gen-visitor.hh"
# include "msc/msc-element.hh"
# include "msc/instance.hh"
# include "msc/strict-order-area.hh"

class Draw : public msc::Visitor
{
  public:
    virtual void operator()(msc::EventArea&);
    virtual void operator()(msc::Instance&);
};

#endif /* !DRAW_HH_ */
