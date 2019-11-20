#pragma once
#include <stdexcept>

#include "./arg.hpp"

class StringArg : public Arg {
 public:
  StringArg(const std::string& sFlag, const std::string& lFlag,
            const std::string& defaultVal = "");

  bool canProcess(const std::string& flag) const override;
  void process(int index, int argc, char** argv) override;
  void xorProcess(int index, int argc, char** argv) override;
  bool isDoneProcessing() const override { return processed; }

  const std::string& getVal() const { return val; }
 private:
  std::string sFlag;
  std::string lFlag;
  std::string val;
  bool processed = false;
};
