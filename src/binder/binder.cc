#include <iostream>
#include "binder/binder.hh"
#include "msc/all.hh"

namespace binder
{
  void Binder::operator()(msc::BasicMsc& bmsc)
  {
    std::cout << "bmsc" << std::endl;
    super::operator()(bmsc);
  }

  void Binder::operator()(msc::Instance& instance)
  {
    std::cout << "instance" << std::endl;
    super::operator()(instance);
  }

  void Binder::operator()(msc::TextDefinition& td)
  {
    std::cout << "textdef" << std::endl;
    super::operator()(td);
  }

  void Binder::operator()(msc::InstanceHead& ih)
  {
    std::cout << "instance head" << std::endl;
    super::operator()(ih);
  }

  void Binder::operator()(msc::Identifier& id)
  {
    std::cout << "identifier" << std::endl;
    super::operator()(id);
  }

  void Binder::operator()(msc::Message& msg)
  {
    std::cout << "message" << std::endl;
    std::cout << "direction: " << msg.direction_ << std::endl;
    std::cout << "instance: " << msg.instance_ << std::endl;
    super::operator()(msg);
  }

  void Binder::operator()(msc::MessageSequenceChart& msc)
  {
    std::cout << "msc:" << *msc.name_ << std::endl;
    super::operator()(msc);
  }

}
