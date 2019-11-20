#include "./string_arg.hpp"

StringArg::StringArg(const std::string& sFlag, const std::string& lFlag,
                     const std::string& defaultVal)
    : Arg(), sFlag(sFlag), lFlag(lFlag), val(defaultVal) {}

bool StringArg::canProcess(const std::string& flag) const {
  return flag == sFlag || flag == lFlag;
}
void StringArg::process(int index, int argc, char** argv) {
  if (index + 1 >= argc) {
    throw std::runtime_error("No argument after the flag");
  }
  val = const_cast<const char*>(argv[index + 1]);
  processed = true;
}

void StringArg::xorProcess(int index, int argc, char** argv) {
  val = "";
  processed = true;
}
