#include "argument_parser.h"


void ArgumentSet::ParseArguments(int argc, char * argv[])
{

  enum State
  {
    DEFAULT = 0,
    NAMED_VALUE = 1
  };

  State state = DEFAULT;
  int i = 1;
  int positionalIndex = 0;
  NamedArgument * namedArgument;

  while (i < argc)
  {

    string entry = string(argv[i]);

    if (state == DEFAULT)
    {
      // check if positional
      if (entry[0] != '-')
      {
        if (positionalIndex < positionalArguments.size())
          positionalArguments[positionalIndex++].value = entry;
        else
          positionalArguments[positionalIndex - 1].value += " " + entry;
      }
      else if (entry[1] != '-')
      {
        // search for named entry
        bool isNamed = false;
        for (auto &e : namedArguments)
          if (e.shorthand == entry[1] && entry.length() == 2)
          {
            isNamed = true;
            namedArgument = &e;
          }

        // continue to next if it is a named entry
        if (isNamed)
        {
          state = NAMED_VALUE;
        }
        else
        {
          // set all matching flags
          for (auto &c : entry.substr(1, entry.length() - 1))
          {
            bool isFlag = false;
            for (auto &f : flags) {
              if (c == f.shorthand) {
                f.set = true;
                isFlag = true;
                break;
              }
            }
            if (!isFlag)
              throw runtime_error("Flag does not exist.");
          }
        }
      }
      else
      {
        string longhand = entry.substr(2, entry.length() - 2);
        // search named
        bool isNamed = false;
        for (auto &e : namedArguments)
        {
          if (e.name == longhand) {
            isNamed = true;
            namedArgument = &e;
            break;
          }
        }
        if (isNamed)
        {
          state = NAMED_VALUE;
        }
        else
        {
          bool isFlag = false;
          for (auto &f : flags)
            if (f.name == longhand) {
              isFlag = true;
              f.set = true;
            }
          if (!isFlag)
            throw runtime_error("Flag does not exist.");
        }
      }
    }
    else {
      namedArgument->value = entry;
      state = DEFAULT;
    }

    i++;
  } // while

}

ArgumentSet & ArgumentSet::AddArgument(Argument * arg)
{
  switch (arg->type)
  {
  case Argument::FLAG:

    break;
  case Argument::NAMED:
    break;
  case Argument::POSITIONAL:
    break;
  }
}

ArgumentSet & ArgumentSet::AddFlag(Flag flag)
{
  if (ShorthandTaken(flag.shorthand))
    throw runtime_error("Shorthand taken.");
  if (NameTaken(flag.name))
    throw runtime_error("Name taken.");

  flags.push_back(flag);
  return *this;
}


ArgumentSet & ArgumentSet::AddNamedArgument(NamedArgument arg)
{
  if (ShorthandTaken(arg.shorthand))
    throw runtime_error("Shorthand taken.");
  if (NameTaken(arg.name))
    throw runtime_error("Name taken.");

  namedArguments.push_back(arg);
  return *this;
}


ArgumentSet & ArgumentSet::AddPositionalArgument(PositionalArgument arg)
{
  if (ShorthandTaken(arg.shorthand))
    throw runtime_error("Shorthand taken.");
  if (NameTaken(arg.name))
    throw runtime_error("Name taken.");

  positionalArguments.push_back(arg);
  return *this;
}


bool ArgumentSet::ShorthandTaken(char shorthand)
{
  for (auto &a : positionalArguments)
    if (a.shorthand != 0 && a.shorthand == shorthand)
      return true;
  for (auto &a : namedArguments)
    if (a.shorthand != 0 && a.shorthand == shorthand)
      return true;
  for (auto &a : flags)
    if (a.shorthand != 0 && a.shorthand == shorthand)
      return true;

  return false;
}


bool ArgumentSet::NameTaken(string name)
{
  for (auto &a : positionalArguments)
    if (a.name == name)
      return true;
  for (auto &a : namedArguments)
    if (a.name == name)
      return true;
  for (auto &a : flags)
    if (a.name == name)
      return true;

  return false;
}