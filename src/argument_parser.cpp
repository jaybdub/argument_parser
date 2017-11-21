#include "argument_parser.h"
#include <stdexcept>

using namespace std;

ArgumentSet::~ArgumentSet() {
  for (auto arg : args)
    delete arg;
}

bool ArgumentSet::HasName(string name) {
  for (auto arg : args)
    if (name == arg->GetName())
      return true;
  return false;
}


bool ArgumentSet::HasShorthand(char shorthand) {
  for (auto arg : args)
    if (arg->GetShorthand() != 0 && shorthand == arg->GetShorthand())
      return true;
  return false;
}


Argument & ArgumentSet::Add(Argument *arg) {
  if (HasShorthand(arg->GetShorthand()))
    throw std::runtime_error("Argument shorthand taken.");
  if (HasName(arg->GetName()))
    throw std::runtime_error("Argument name taken.");
  args.push_back(arg);
  return *arg;
}

Argument & ArgumentSet::AddFlag(string name) {
  Argument * arg = new Flag(name);
  return Add(arg);
}


Argument & ArgumentSet::AddPositionalArgument(string name) {
  Argument * arg = new PositionalArgument(name);
  return Add(arg);
}


Argument & ArgumentSet::AddNamedArgument(string name) {
  Argument * arg = new NamedArgument(name);
  return Add(arg);
}


Argument * ArgumentSet::GetPositionalArgument(size_t pos) {
  size_t count = 0;

  for (auto a : args) {
    if (a->GetType() == Argument::POSITIONAL && count == pos)
      return a;
    if (a->GetType() == Argument::POSITIONAL)
      count++;
  }

  return nullptr;
}

Argument * ArgumentSet::GetArgument(string name) {
  for (auto a : args)
    if (a->GetName() == name)
      return a;
  return nullptr;
}

Argument * ArgumentSet::GetArgument(char shorthand) {
  for (auto a : args)
    if (a->GetShorthand() == shorthand)
      return a;
  return nullptr;
}

void ArgumentSet::Parse(int argc, char * argv[]) {
  int isValue = 0;
  int pos = 0;
  Argument *a = nullptr;

  for (int i = 1; i < argc; i++) {
    string entry = argv[i];
    if (!isValue) { 
      if (entry[0] != '-') {
        a = GetPositionalArgument(pos++);
        if (a == nullptr)
          throw runtime_error("Too many positional arguments.");
        a->SetValue(entry);
      } else if (entry[1] != '-') {        
        a = GetArgument(entry[1]);
        if (a == nullptr)
          throw runtime_error("Invalid argument shorthand.");
        if (a->GetType() == Argument::FLAG) {
          a->SetValue("1");
          // parse additional flags
          for (auto c : entry.substr(2, entry.length() - 2)) {
            a = GetArgument(c);
            if (a == nullptr)
              throw runtime_error("Invalid argument shorthand.");
            if (a->GetType() != Argument::FLAG)
              throw runtime_error("Shorthand is not for flag.");
            a->SetValue("1");
          }
        } else {
          if (entry.length() > 2)
            throw runtime_error("Invalid argument shorthand.");
          isValue = 1;
        }
      } else {
        a = GetArgument(entry.substr(2, entry.length() - 2));
        if (a == nullptr)
          throw runtime_error("Invalid argument name.");
        if (a->GetType() == Argument::FLAG)
          a->SetValue("1");
        else
          isValue = 1;
      }
    } else {
      a->SetValue(entry);
      isValue = 0;
    }
  } 
}
