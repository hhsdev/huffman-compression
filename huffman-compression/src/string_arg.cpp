#include "./string_arg.hpp"

StringArg::StringArg(const std::string& shortFlag, const std::string& longFlag,
                     const std::string& defaultValue)
    : Arg(shortFlag, longFlag), value(defaultValue) {}

void StringArg::process(int index, int argc, char** argv) {
  if (index + 1 >= argc) {
    throw std::runtime_error("No argument after the flag");
  }
  value = const_cast<const char*>(argv[index + 1]);
  resolve();
}

void StringArg::xorProcess() {
  value = "";
  resolve();
}
