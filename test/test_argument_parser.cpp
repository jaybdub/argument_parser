#include "argument_parser.h"
#include <exception>
#include <iostream>


void test_argument_parser(int argc, char * argv[])
{
  ArgumentSet argset;
  argset.Add(Flag("help", 'h'));
  argset.Add(PositionalArgument("input"));
  argset.Add(PositionalArgument("output"));

//  char * argv[] = { "exe", "-h" }; int argc = sizeof(argv) / 8;

  argset.Parse(argc, argv);

  cout << argset.HelpString() << endl;
}

int main(int argc, char * argv[])
{
  test_argument_parser(argc, argv);
  return 0;
}