#pragma once
#include <string>
#include "./arg.hpp"

class Flag : public Arg {
 public:
  Flag(const std::string& shortFlag, const std::string& longFlag,
       const bool defaultVal = false);
  void set(bool newVal);
  operator bool();
   
  bool canProcess(const std::string& arg) const override;

  void process(int index, int argc, char** argv) override;
  void xorProcess(int index, int argc, char** argv) override;
  bool isDoneProcessing() const override { return processed; }
 private:
  std::string sFlag;
  std::string lFlag;
  bool val;
  bool processed = false;
};
