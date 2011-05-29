# include "msc/message-sequence-chart.hh"

namespace msc
{
  MessageSequenceChart::MessageSequenceChart(const String&      name,
                                             virtuality_enum    virtuality,
                                             Msc*               msc)
    : Labelable(name), virtuality_ (virtuality), msc_ (msc)
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
