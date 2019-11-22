#pragma once
#include "./flag.hpp"
#include <vector>

class CommandLine {
 public:
  CommandLine() = default;
  void parse(int argc, char** argv);
  void add(Arg& arg);
  void xorAdd(Arg& a, Arg& b);
 private:
  std::vector<Arg*> args;
  std::vector<std::pair<Arg*, Arg*>> xorArgs;
  
  void passToNormalArguments(int index);
  void passToXoredArguments(int index);
  int argument_count;
  char** argument_values;
};
