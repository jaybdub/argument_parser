#ifndef ARGUMENT_PARSER_IMP_H
#define ARGUMENT_PARSER_IMP_H

#include <string>
#include <vector>

using namespace std;


struct Argument {

protected:
  string name;
  string description = ""; 
  char shorthand = 0;
  string value = "";
  string defaultValue = "";

public:
  enum Type {
    FLAG,
    NAMED,
    POSITIONAL
  };

  virtual ~Argument() {};
  Argument(string name) : name(name) {};
  Argument(string name, string description) : name(name), description(description) {};
  Argument(string name, string description, char shorthand) 
    : name(name), description(description), shorthand(shorthand) {};
  string GetName() { return name; };
  string GetDescription() { return description; };
  string GetValue() { return value; };
  char GetShorthand() { return shorthand; };
  virtual Type GetType() = 0;
  void SetValue(string value) { this->value = value; };
  Argument & Shorthand(char shorthand) { 
    this->shorthand = shorthand;
    return *this; 
  };
  Argument & Description(string shorthand) {
    this->description = description; 
    return *this;
  };
  Argument & Default(string value) {
    this->defaultValue = value;
    this->value = value;
    return *this;
  }

};


struct Flag : public Argument {
  Flag(string name) : Argument(name) { value = "0"; };
  Flag(string name, string description) : Argument(name, description) { value = "0";};
  Flag(string name, string description, char shorthand) 
    : Argument(name, description, shorthand) { value = "0"; };
  Type GetType() override { return FLAG; };
};


struct NamedArgument : public Argument {
  NamedArgument(string name) : Argument(name) {};
  NamedArgument(string name, string description) : Argument(name, description) {};
  NamedArgument(string name, string description, char shorthand) 
    : Argument(name, description, shorthand) {};
  Type GetType() override { return NAMED; };
};


struct PositionalArgument : public Argument {
  PositionalArgument(string name) : Argument(name) {};
  PositionalArgument(string name, string description) : Argument(name, description) {};
  PositionalArgument(string name, string description, char shorthand) 
    : Argument(name, description, shorthand) {};
  Type GetType() override { return POSITIONAL; };
};


class ArgumentSet {
  vector<Argument*> args;
  Argument & Add(Argument *arg);
public:
  ~ArgumentSet();
  Argument & AddFlag(string name);
  Argument & AddNamedArgument(string name);
  Argument & AddPositionalArgument(string name);
  void Parse(int argc, char * argv[]);
  bool HasName(string name);
  bool HasShorthand(char shorthand);
  Argument * GetPositionalArgument(size_t pos);
  Argument * GetArgument(string name);
  Argument * GetArgument(char shorthand);
  vector<Argument*> & GetArguments() {
    return args;
  }
};


#endif
