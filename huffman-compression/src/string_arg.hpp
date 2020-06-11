#pragma once
#include <stdexcept>

#include "./arg.hpp"

class StringArg : public Arg {
 public:
  StringArg(const std::string& sFlag, const std::string& lFlag,
            const std::string& defaultVal = "");
  void process(int index, int argc, char** argv) override;
  void xorProcess() override;
  const std::string& getValue() const { return value; }
 private:
  std::string value;
};
