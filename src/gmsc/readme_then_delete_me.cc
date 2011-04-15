#include "draw.hh"
#include <iostream>
#include "misc/any.hh"
#include "boost/variant.hpp"

void Draw::operator()(msc::EventArea& e)
{
  GEventArea& gi = (GEventArea&)(e);

  std::cout << "ge";
}

void Draw::operator()(msc::Instance& e)
{
  GInstance& gi = (GInstance&)(e);

  std::cout << "gi : ";
  accept(gi.element_->last_);
}
