#include <iostream>
#include "parse/parser.hh"
#include "msc/ast.hh"
#include "msc/pretty-printer.hh"

int main(int argc, char* argv[])
{
  if (argc != 3)
    return 1;

  parse::Parser parser((pANTLR3_UINT8) argv[2]);
  msc::Ast*     ast = parser.parse(argv[1][0] == '1');

  if (parser.error_count_get())
    return 1;

  msc::PrettyPrinter printer(std::cout);
  printer(*ast);

  return 0;
}
