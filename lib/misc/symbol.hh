#ifndef MISC_SYMBOL_HH
# define MISC_SYMBOL_HH

# include <set>
# include <string>
# include <iosfwd>
# include "misc/unique.hh"

namespace misc
{
  /** \brief Define symbol class.
   *
   * Map any string to a unique reference.
   * This allows to avoid an "strcmp ()" style comparison of strings:
   * reference comparison is much faster.
   */
  class Symbol : public Unique<std::string>
  {
    private:
      typedef Unique<std::string> super_type;

      /// The set of strings type.
      typedef super_type::object_set_type string_set_type;

      /// The type for the size of string map.
      typedef string_set_type::size_type string_size_type;

      /** \name Ctor & Dtor.
       * \{ */
    public:
      /// Construct a symbol.
      Symbol(const std::string&);

      /// Construct a symbol.
      Symbol(const char*);

      /// Destroy a symbol.
      virtual ~Symbol();
      /** \} */

      /** \name Accessors.
       * \{ */
    public:
      /// Return the string referenced by this.
      const std::string& name_get() const;

      /// Return the number of referenced strings.
      static string_size_type string_map_size();
      /** \} */

      /** \name Operators.
       ** \{ */
    public:
      /// Assign a symbol to this symbol.
      Symbol& operator=(const Symbol&);

      /// Compare two symbol for equality.
      bool operator==(const Symbol&) const;

      /// Compare two symbol for inequality.
      bool operator!=(const Symbol&) const;
      /** \} */

      /** \name Factory methods.
       * \{ */
    public:
      /// Create a new unique symbol.
      static Symbol fresh();
      /// Create a new unique symbol, forged from \a s.
      static Symbol fresh(const Symbol&);
      /** \} */
  };

  /** \brief Intercept output stream redirection.
   ** \param ostr the destination output stream
   ** \param the a reference to the symbol to redirect
   */
  std::ostream& operator<<(std::ostream&, const Symbol&);
}

# include "misc/symbol.hxx"

#endif // !MISC_SYMBOL_HH
