#ifndef MISC_EXCEPTION_HH_
# define MISC_EXCEPTION_HH_

# include <exception>
# include <string>

namespace misc
{
  class Exception : std::exception
  {
    public:
      Exception(const char*);
      virtual ~Exception() throw ();

      virtual const char* what() const throw();

    protected:
      const std::string message_;
  };
} // namespace misc

#endif /* !MISC_EXCEPTION_HH_ */
