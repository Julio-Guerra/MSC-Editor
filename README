This software was suggested by Julien Delange and was realised by two
EPITA students, Julio Guerra and Patrick Samy.

# Purpose #
MSC is a graphical and textual language for the description and
specification of the interactions between system components. The main
area of application for Message Sequence Charts is as an overview
specification of the communication behaviour of real-time systems, in
particular telecommunication switching systems. Message Sequence
Charts may be used for requirement specification, simulation and
validation, test-case specification and documentation of real-time
systems. MSCs are often used in combination with SDL, in particular
the ITU specification and description language.

# Project Layout #
lib:                    Independent Tools.
lib/misc:               Project Independent Tools.
lib/libantlr3c-3.1.3:   ANTLR3 C Library.
src:                    Project Dependant Sources.
src/parse:              Parsing.
src/msc:                MSC's Abstract Syntax Tree.
src/gui:                GUI Front-Ends & User Flow Logic.
src/gui/qt:             Qt Front-End.
src/view:               MSC Abstrat Syntax Tree Decorator.
src/view/qt:            Qt Decorator.
tests:                  Unit & Functional Tests.
tests/parse:            Parser Tests.

# Project Architecture #
MSC Editor is simply composed of two layers: the back-end and the
front-end. The front-end uses back-end's features. So the back-end is
absolutely abstracted from any usage.

## Back-End
The back-end provides everything required to handle a MSC document: an
abstract syntax tree (AST), a lexer, a parser and AST's visitors.


### Parser
The parser takes an input and the standard it follows (MSC96 or
MSC2000) to generate the MSC's AST. The AST is represented in the
technical documentation (make doc) of `msc::Ast` class.

A DefaultVisitor provides the default traversal behavior of the
AST. Its first usage is the `PrettyPrinter` visitor thats prints an
AST without caring of how to traverse the AST, this is delegated to
the `DefaultVisitor` super class. So many other Visitors can be
imagined and they simply have to inherit from `DefaultVisitor`.

## Front-End
The front-end's first goal is to make the AST drawable by the target
GUI. The decorator design pattern should be used for that purpose,
making the drawable AST, a normal AST, i.e. compatible with every
back-end feature.

Many front-ends can be implemented, using this same back-end.

### View
This can be considered as the border between the back-end and the
front-end. It simply defines graphical AST nodes for the target.


### GUI
The GUI simply handles the graphical interface and user interactions.

# Test Suite #
Run the testsuite.sh script in the directory tests/ with the project
fully compiled.
