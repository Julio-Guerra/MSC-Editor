#ifndef COMPLETE_MESSAGE_HH_
# define COMPLETE_MESSAGE_HH_

# include "msc/msc-message.hh"
# include "msc/event.hh"
# include "msc/gen-visitor.hh"

namespace msc
{
  class CompleteMessage : public MscMessage
  {
    public:
      virtual void accept(Visitor&);

    private:
      Event*    sender_;

      Event*    receiver_;
  };
} // namespace msc

#endif /* !COMPLETE_MESSAGE_HH_ */
