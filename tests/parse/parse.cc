#include "parse/parser.hh"

int main(int argc, char* argv[])
{
  if (argc != 3)
    return 1;

  parse::Parser parser((pANTLR3_UINT8) argv[2]);
  parser.parse(argv[1][0] == '1');
  return parser.error_count_get();
}
