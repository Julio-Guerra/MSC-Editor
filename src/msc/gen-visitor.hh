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
      void operator()(Ast&);

      /** Basic MSC visitor's pure abstract methods.
       * \{ */
      virtual void operator()(MessageSequenceChart&) = 0;
      virtual void operator()(BasicMsc&) = 0;
      virtual void operator()(Instance&) = 0;
      virtual void operator()(InstanceHead&) = 0;
      virtual void operator()(Identifier&) = 0;
      virtual void operator()(Message&) = 0;
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
