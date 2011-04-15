#ifndef INCOMPLETE_MESSAGE_HH_
# define INCOMPLETE_MESSAGE_HH_

# include "msc/msc-message.hh"
# include "msc/gen-visitor.hh"

namespace msc
{
  class IncompleteMessage : public MscMessage
  {
    public:
      enum message_kind_e
      {
        LOST,
        FOUND
      };
      typedef enum message_kind_e message_kind_e;

      virtual void accept(Visitor&);

    private:
      Label             instance_label_;

      Label             dot_label_;

      message_kind_e    message_kind_;
  }
} // namespace msc

#endif /* !INCOMPLETE_MESSAGE_HH_ */
