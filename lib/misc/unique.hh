#ifndef MISC_UNIQUE_HH
# define MISC_UNIQUE_HH

# include <set>
# include <iosfwd>

namespace misc
{

  /** \brief Define \c Unique class.
   *
   * Implementation of the flyweight design pattern.
   * Map identical objects to a unique reference.
   */
  template <typename T, class C = std::less<T> >
  class Unique
  {
    public:
      /// The unique's object type.
      typedef std::set<T, C> object_set_type;

      /// The type for the size of the unique set.
      typedef typename object_set_type::size_type object_size_type;

      typedef Unique<T, C> value_type;

      typedef T data_type;

      /** \name Ctor & Dtor.
       * \{ */
      /// Construct a \c unique.
      Unique(const data_type&);

      virtual ~Unique();
      /** \} */

      /** \name Accessors.
       * \{ */
      /// Return the object referenced by \c this.
      virtual const data_type& object_get() const;
      virtual operator const data_type&() const;

      /// Return the number of referenced objects.
      static object_size_type object_map_size();
      /** \} */

      /** \name Operators.
       * \{ */
      /// Assign a \c Unique to this \c Unique.
      virtual value_type& operator=(const value_type&);

      /// Compare two \c unique for equality.
      virtual bool operator==(const value_type&) const;

      /// Compare two \c Unique for inequality.
      virtual bool operator!=(const value_type&) const;

      /// Compare two \c Unique for order.
      virtual bool operator<(const value_type&) const;
      /** \} */

    protected:
      /// Return the set of uniques.
      static object_set_type& object_set_instance();

      /// Pointer to the unique referenced object.
      const data_type* obj_;
  };

  /// Intercept output stream redirection.
  template <typename T, class C>
  std::ostream& operator<< (std::ostream&, const Unique<T, C>&);
}

# include "misc/unique.hxx"

#endif // !MISC_UNIQUE_HH
