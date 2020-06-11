#pragma once
#include <exception>
#include <string>
#include "./command_line.hpp"
#include "./flag.hpp"
#include "./string_arg.hpp"

class ConfigException : public std::exception {
 public:
  ConfigException(const std::string& reason) : mReason(reason) {}

  virtual const char* what() const noexcept override { return mReason.c_str(); }

 private:
  std::string mReason;
};

class Config {
 public:
  enum Mode { COMPRESS, DECOMPRESS };
  Config() = default;

  void update(int argc, char** argv);
  void printHelp() const;

  const std::string& getInputFile() { return input_file; }
  const std::string& getOutputFile() { return output_file; }

  Mode getMode() { return mode; }
  Mode setMode(Mode newMode) { mode = newMode; }

 private:
  std::string input_file;
  std::string output_file;

  Mode mode = COMPRESS;
};
