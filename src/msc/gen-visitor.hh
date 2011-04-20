#ifndef GEN_VISITOR_HH_
# define GEN_VISITOR_HH_

# include "msc/fwd.hh"

namespace msc
{
  /** \brief Root class of all MSC visitors.
   *
   * GenVisitor is the root class of all MSC visitors.
   * The visited MSC is not const; so derived visitors can change
   * properties.
   */
  class GenVisitor
  {
    public:
      /// Entry point of the visitor.
      void operator()(MscElement&);

      /** Low Level MSC visitor's abstract methods.
       * \{ */
      virtual void operator()(EventArea&) = 0;
      virtual void operator()(Instance&) = 0;
      virtual void operator()(MscMessage&) = 0;
      virtual void operator()(Msc&) = 0;
      virtual void operator()(BasicMsc&) = 0;
      virtual void operator()(Event&) = 0;
      virtual void operator()(IncompleteMessage&) = 0;
      virtual void operator()(StrictOrderArea&) = 0;
      virtual void operator()(CoregionArea&) = 0;
      virtual void operator()(CompleteMessage&) = 0;
      virtual void operator()(StrictEvent&) = 0;
      virtual void operator()(CoregionEvent&) = 0;
      virtual void operator()(CoregionEventRelation&) = 0;

      /** High Level MSC visitor's abstract methods.
       * \} */
      virtual void operator()(ConnectionNode&) = 0;
      /** \} */
    protected:
      /** A shortcut for recurring code like this:
       *  \code
       *  if (e)
       *    e->accept (*this);
       *  \endcode
       */
      template <class E>
      void accept(E* e);
  };

  typedef GenVisitor Visitor;

} // namespace msc

# include "gen-visitor.hxx"

#endif /* !GEN_VISITOR_HH_ */
