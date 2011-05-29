#ifndef MSC_MESSAGE_SEQUENCE_CHART_HH_
# define MSC_MESSAGE_SEQUENCE_CHART_HH_

# include <boost/shared_ptr.hpp>

# include "msc/ast.hh"
# include "msc/labelable.hh"
# include "msc/gen-visitor.hh"
# include "msc/msc.hh"

namespace msc
{
  class MessageSequenceChart : public Ast, public Labelable
  {
    public:
      typedef enum
      {
        VIRTUAL = 0,
        REDEFINED,
        FINALIZED,
        UNKNOWN
      } virtuality_enum;

      /// \name Ctor & Dtor.
      /// \{
      MessageSequenceChart(const String&, virtuality_enum, Msc*);

      virtual ~MessageSequenceChart();
      /// \}

      /// \name Accessors.
      /// \{
      virtuality_enum   virtuality_get();

      pMsc              msc_get();
      /// \}

      /// \name Visitor entry point.
      /// \{
      virtual void accept(Visitor&);
      /// \}

    private:
      /// Virtuality of the MSC.
      virtuality_enum           virtuality_;

      /// Pointer to a BasicMsc or a HighMsc.
      pMsc                      msc_;
  };
} // namespace msc

# include "msc/message-sequence-chart.hxx"

#endif /* !MSC_MESSAGE_SEQUENCE_CHART_HH_ */
