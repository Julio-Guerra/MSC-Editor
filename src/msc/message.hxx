#ifndef MESSAGE_HXX_
# define MESSAGE_HXX_

# include "msc/message.hh"

namespace msc
{
  inline void Message::from_set(Instance*       from)
  {
    from_ = from;
  }

  inline pInstance Message::from_get() const
  {
    return from_;
  }

  inline void Message::to_set(Instance*          to)
  {
    to_ = to;
  }

  inline pInstance Message::to_get() const
  {
    return to_;
  }

} // namespace msc

#endif /* !MESSAGE_HXX_ */
