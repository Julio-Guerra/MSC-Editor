#ifndef MESSAGE_SEQUENCE_CHART_HH_
# define MESSAGE_SEQUENCE_CHART_HH_

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

      /// Ctor & dtor
      /// \{
      MessageSequenceChart(virtuality_enum, Msc*);

      virtual ~MessageSequenceChart();
      /// \}

      virtual void accept(Visitor&);

    private:
      virtuality_enum           virtuality_;

      /// Pointer to a BasicMsc or a HighMsc.
      /// The shared_ptr make the default copy constructor safe.
      pMsc                      msc_;
  };
} // namespace msc

#endif /* !MESSAGE_SEQUENCE_CHART_HH_ */
