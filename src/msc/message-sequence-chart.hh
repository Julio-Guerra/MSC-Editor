#ifndef MESSAGE_SEQUENCE_CHART_HH_
# define MESSAGE_SEQUENCE_CHART_HH_

# include "msc/ast.hh"
# include "msc/labelable.hh"
# include "msc/gen-visitor.hh"

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

      /// Ctor & dtor
      /// \{
      MessageSequenceChart(virtuality_enum, int);
      virtual ~MessageSequenceChart();
      /// \}

      virtual void accept(Visitor&);

    private:
  };
} // namespace msc

#endif /* !MESSAGE_SEQUENCE_CHART_HH_ */
