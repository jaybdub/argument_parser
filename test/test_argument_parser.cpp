#include "argument_parser.h"
#include <exception>
#include <iostream>

using namespace std;

void test_argument_parser(int argc, char * argv[])
{
  ArgumentSet a;
  a.Add(new Flag("hello", "Set this to hello.", 'h'));
  a.Add(new Flag("goodbye", "Set this to goodbye.", 'g'));
  a.Add(new PositionalArgument("okay"));
  a.Add(new NamedArgument("bleh", "Set this to blebleh.", 'b'));
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
