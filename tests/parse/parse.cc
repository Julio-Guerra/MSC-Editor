#include "parse/parser.hh"

int main(int argc, char* argv[])
{
  if (!argc)
    return 1;

  parse::Parser parser((pANTLR3_UINT8) argv[1]);
  parser.parse();
  return parser.error_count_get();
}
