#include <iostream>
#include "parse/parser.hh"
#include "msc/ast.hh"
#include "msc/pretty-printer.hh"

int main(int argc, char* argv[])
{
  parse::Parser parser((pANTLR3_UINT8) argv[1]);
  msc::Ast*     ast = parser.parse();

  if (parser.error_count_get())
    return 1;

  msc::PrettyPrinter printer(std::cout);
  printer(*ast);

  return 0;
}
