# include "msc/message-sequence-chart.hh"

namespace msc
{
  MessageSequenceChart::MessageSequenceChart(virtuality_enum    virtuality,
                                             Msc*               msc)
    : virtuality_ (virtuality), msc_ (msc)
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
