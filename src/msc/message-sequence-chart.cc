# include "msc/message-sequence-chart.hh"

#include <iostream>

namespace msc
{
  MessageSequenceChart::MessageSequenceChart(virtuality_enum virtuality, int n)
  {
    std::cout << virtuality << " " << UNKNOWN << std::endl;
    std::cout << "n = " << n << std::endl;
  }

  MessageSequenceChart::~MessageSequenceChart()
  {
  }

  void MessageSequenceChart::accept(Visitor& v)
  {
    v(*this);
  }
}
