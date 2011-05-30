#ifndef PARSER_HH_
# define PARSER_HH_

# include "parse/MscParser.h"
# include "parse/MscLexer.h"
# include "msc/ast.hh"

namespace parse
{
  class Parser
  {
    public:
      /// \name Ctor & Dtor.
      /// \{
      Parser(pANTLR3_UINT8);

      ~Parser();
      /// \}

      /// Parse the input and return a pointer to the created AST.
      msc::Ast* parse() throw();

      /// Get the number of errors during the parsing.
      int       error_count_get() const;

    private:
      /// Name of the input file.  Note that we always use the
      /// abstract type pANTLR3_UINT8 for ASCII/8 bit strings - the
      /// runtime library guarantees that this will be good on all
      /// platforms. This is a general rule - always use the ANTLR3
      /// supplied typedefs for pointers/types/etc.
      pANTLR3_UINT8                     filename_;

      /// The ANTLR3 character input stream, which abstracts the input
      /// source such that it is easy to provide input from different
      /// sources such as files, or memory strings.  For an
      /// 8Bit/latin-1/etc memory string use: input =
      /// antlr3New8BitStringInPlaceStream (stringtouse,
      /// (ANTLR3_UINT32) length, NULL); For a UTF16 memory string
      /// use: input = antlr3NewUTF16StringInPlaceStream (stringtouse,
      /// (ANTLR3_UINT32) length, NULL); For input from a file, see
      /// code below Note that this is essentially a pointer to a
      /// structure containing pointers to functions.  You can create
      /// your own input stream type (copy one of the existing ones)
      /// and override any individual function by installing your own
      /// pointer after you have created the standard version.
      pANTLR3_INPUT_STREAM              input_;

      /// The lexer is of course generated by ANTLR, and so the lexer type
      /// is not upper case.  The lexer is supplied with a
      /// pANTLR3_INPUT_STREAM from whence it consumes its input and
      /// generates a token stream as output. This is the ctx (CTX
      /// macro) pointer for your lexer.
      pMscLexer                         lexer_;

      /// The token stream is produced by the ANTLR3 generated
      /// lexer. Again it is a structure based API/Object, which you
      /// can customise and override methods of as you wish. a Token
      /// stream is supplied to the generated parser, and you can
      /// write your own token stream and pass this in if you wish.
      pANTLR3_COMMON_TOKEN_STREAM       token_stream_;

      /// The Lang parser is also generated by ANTLR and accepts a
      /// token stream as explained above. The token stream can be any
      /// source in fact, so long as it implements the
      /// ANTLR3_TOKEN_SOURCE interface. In this case the parser does
      /// not return anything but it can of course specify any kind of
      /// return type from the rule you invoke when calling it. This
      /// is the ctx (CTX macro) pointer for your parser.
      pMscParser                        parser_;
  };
} // namespace parse

# include "parse/parser.hxx"

#endif /* !PARSER_HH_ */
