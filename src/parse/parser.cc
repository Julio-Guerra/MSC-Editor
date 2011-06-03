#include "parse/parser.hh"
#include "parse/exception.hh"

/// Global variable used by the (C) parser informing about the input
/// standard.
bool __msc96;

namespace parse
{
  Parser::Parser(pANTLR3_UINT8  filename)
    : filename_ (filename),
      input_ (0),
      lexer_ (0),
      token_stream_ (0),
      parser_ (0)
  {
  }

  Parser::~Parser()
  {
    if (parser_)
    {
      parser_->free(parser_);
      token_stream_->free(token_stream_);
      lexer_->free(lexer_);
      input_->close(input_);
    }
  }

  void Parser::prepare() throw()
  {
    // Create the input stream using the supplied file name (Use
    // antlr38BitFileStreamNew for UTF16 input).
    input_ = antlr3AsciiFileStreamNew(filename_);

    // The input will be created successfully, providing that there is
    // enough memory and the file exists, etc.
    if (!input_)
      throw Exception((std::string("Unable to open file ")
                       + std::string((char*) filename_)
                       + std::string(" due to malloc() failure.")).c_str());

    /// Our input stream is now open and all set to go, so we can
    /// create a new instance of our lexer and set the lexer input to
    /// our input stream: (file | memory | ?) --> inputstream -> lexer
    /// --> tokenstream --> parser ( --> treeparser )?
    lexer_ = MscLexerNew(input_);

    if (!lexer_)
      throw Exception("Unable to create the lexer due to malloc() failure.\n");

    /// Our lexer is in place, so we can create the token stream from it
    /// NB: Nothing happens yet other than the file has been read. We
    /// are just connecting all these things together and they will be
    /// invoked when we call the parser rule. ANTLR3_SIZE_HINT can be
    /// left at the default usually unless you have a very large token
    /// stream/input. Each generated lexer provides a token source
    /// interface, which is the second argument to the token stream
    /// creator.  Note tha even if you implement your own token
    /// structure, it will always contain a standard common token within
    /// it and this is the pointer that you pass around to everything
    /// else. A common token as a pointer within it that should point to
    /// your own outer token structure.
    token_stream_ = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT,
                                                     TOKENSOURCE(lexer_));

    if (!token_stream_)
      throw Exception("Out of memory trying to allocate token stream.");

    parser_ = MscParserNew(token_stream_);

    if (!parser_)
      throw Exception("Out of memory trying to allocate parser.");

    // We are all ready to go. Though that looked complicated at first
    // glance, I am sure, you will see that in fact most of the code
    // above is dealing with errors and there isn;t really that much to
    // do (isn;t this always the case in C? ;-).
    //
    // So, we now invoke the parser. All elements of ANTLR3 generated C
    // components as well as the ANTLR C runtime library itself are
    // pseudo objects. This means that they are represented as pointers
    // to structures, which contain any instance data they need, and a
    // set of pointers to other interfaces or 'methods'. Note that in
    // general, these few pointers we have created here are the only
    // things you will ever explicitly free() as everything else is
    // created via factories, that allocate memory efficiently and
    // free() everything they use automatically when you close the
    // parser/lexer/etc.
    //
    // Note that this means only that the methods are always called via
    // the object pointer and the first argument to any method, is a
    // pointer to the structure itself.  It also has the side advantage,
    // if you are using an IDE such as VS2005 that can do it that when
    // you type ->, you will see a list of all the methods the object
    // supports.
  }

  msc::Ast*     Parser::parse() throw()
  {
    if (!parser_)
    {
      // first use of parse()
      prepare();

      // This grammar rule is specially written to find out which version on
      // the standard is used. It allows to set the global variable __msc96
      // used by semantic predicates in the parser.
      __msc96 = parser_->is_msc96(parser_);
    }
    else
      reset();

    return parser_->parse(parser_);
  }

  void          Parser::reset()
  {
    if (!lexer_ || !parser_ || !input_)
      return;

    input_->reset(input_);
    lexer_->reset(lexer_);
    parser_->reset(parser_);
  }
} // namespace msc
