#include "./flag.hpp"

Flag::Flag(const std::string& shortFlag, const std::string& longFlag,
           const bool defaultVal)
    : Arg(), sFlag(shortFlag), lFlag(longFlag), val(defaultVal) {}

void Flag::set(bool newVal) { val = newVal; }

Flag::operator bool() { return val; }

bool Flag::canProcess(const std::string& arg) const {
  return arg == sFlag || arg == lFlag;
}

void Flag::process(int, int, char**) {
  val = true;
  processed = true;
}

void Flag::xorProcess(int index, int argc, char** argv) {
  val = false;
  processed = true;
}
