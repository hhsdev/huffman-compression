#pragma once
#include "./flag.hpp"
#include "./string_arg.hpp"
#include "./command_line.hpp"

class Config {
 public:
  enum Mode { COMPRESS, DECOMPRESS };
  Config() = default;
  
  void update(int argc, char** argv);

  const std::string& getInputFile() { return input_file; }
  const std::string& getOutputFile() { return output_file; }

  Mode getMode() { return mode; }
  Mode setMode(Mode newMode) { mode = newMode; }
 private:
  std::string input_file;
  std::string output_file;

  Mode mode = COMPRESS;
};
