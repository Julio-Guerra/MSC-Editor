#ifndef MESSAGE_SEQUENCE_CHART_HXX_
# define MESSAGE_SEQUENCE_CHART_HXX_

# include "msc/message-sequence-chart.hh"

namespace msc
{
  inline
  MessageSequenceChart::virtuality_enum MessageSequenceChart::virtuality_get()
  {
    return virtuality_;
  }

  inline pMsc              MessageSequenceChart::msc_get()
  {
    return msc_;
  }
} // namespace msc

#endif /* !MESSAGE_SEQUENCE_CHART_HXX_ */
