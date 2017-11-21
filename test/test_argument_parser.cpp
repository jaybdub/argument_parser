#include "argument_parser.h"
#include <exception>
#include <iostream>

using namespace std;

void test_argument_parser(int argc, char * argv[])
{
  ArgumentSet a;
  a.AddFlag("help")->Description("help to have")->Shorthand('h');
  a.AddNamedArgument("named_arg")->Shorthand('n');
  a.AddPositionalArgument("pos_arg")->Description("a positional argument");

  a.Parse(argc, argv);
  for (auto arg : a.args) {
    cout << arg->GetName() << "(" << arg->GetDescription() << "): " << arg->GetValue() << endl;
  }
}

int main(int argc, char * argv[])
{
  test_argument_parser(argc, argv);
  return 0;
}
