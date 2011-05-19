# include "msc/message-sequence-chart.hh"

namespace msc
{
  MessageSequenceChart::MessageSequenceChart(String*            name,
                                             virtuality_enum    virtuality,
                                             Msc*               msc)
    : name_ (name), virtuality_ (virtuality), msc_ (msc)
  {
  }

  MessageSequenceChart::~MessageSequenceChart()
  {
  }

  void MessageSequenceChart::accept(Visitor& v)
  {
    v(*this);
  }
}
