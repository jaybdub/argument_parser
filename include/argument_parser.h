#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <utility>
#include <unordered_map>
#include <string>
#include <exception>
#include <sstream>
#include <vector>

using namespace std;


struct Argument
{
  const string name;
  const char shorthand = 0;
  Argument(string name) : name(name) {};
  Argument(string name, char shorthand) : name(name), shorthand(shorthand) {};
  virtual string HelpString() = 0;
};

struct Flag : public Argument
{
  Flag(string name) : Argument(name) {};
  Flag(string name, char shorthand) : Argument(name, shorthand) {};
  bool set = false;
  string HelpString();
};

struct NamedArgument : public Argument
{
  NamedArgument(string name) : Argument(name) {};
  NamedArgument(string name, char shorthand) : Argument(name, shorthand) {};
  string value;
  string HelpString();
};

struct PositionalArgument : public Argument
{
  PositionalArgument(string name) : Argument(name, shorthand) {};
  string value;
  string HelpString();
};

struct ArgumentSet
{
  vector<PositionalArgument> positionalArguments;
  vector<NamedArgument> namedArguments;
  vector<Flag> flags;
  void Parse(int argc, char **argv);
  string HelpString();
  ArgumentSet & Add(Flag arg);
  ArgumentSet & Add(NamedArgument arg);
  ArgumentSet & Add(PositionalArgument arg);
  ArgumentSet & AddFlag(Flag flag);
  ArgumentSet & AddNamedArgument(NamedArgument arg);
  ArgumentSet & AddPositionalArgument(PositionalArgument arg);
  bool ShorthandTaken(char shorthand);
  bool NameTaken(string name);
};


#endif  // ARGUMENT_PARSER_H
