#include "./flag.hpp"

Flag::Flag(const std::string& shortFlag, const std::string& longFlag,
           const bool defaultValue)
    : Arg(shortFlag, longFlag), value(defaultValue) {}

void Flag::set(bool newValue) { value = newValue; }

Flag::operator bool() { return value; }

void Flag::process(int, int, char**) {
  value = true;
  resolved = true;
}

void Flag::xorProcess() {
  value = false;
  resolved = true;
}
