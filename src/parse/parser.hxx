#ifndef PARSER_HXX_
# define PARSER_HXX_

# include "parse/parser.hh"

namespace parse
{
  inline int Parser::error_count_get() const
  {
    if (!parser_)
      return -1;

    return parser_->pParser->rec->state->errorCount;
  }
}

#endif /* !PARSER_HXX_ */
