#include "parse/parser.hh"

int main(int argc, char* argv[])
{
  parse::Parser parser((pANTLR3_UINT8) argv[1]);

  msc::Ast*     ast = parser.parse();

  if (!ast)
    return 1;

  return 0;
}
