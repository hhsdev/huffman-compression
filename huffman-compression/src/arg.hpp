#pragma once
#include <string>
class Arg {
 public:
  Arg(const std::string& shortFlag, const std::string& longFlag)
      : shortFlag(shortFlag), longFlag(longFlag) {}
  bool canProcess(const std::string& flag) const {
	return flag == shortFlag || flag == longFlag;
  }
  virtual void process(int index, int argc, char** argv) = 0;
  virtual void xorProcess() = 0;

  virtual void resolve() { resolved = true; }
  virtual bool isResolved() const { return resolved; }
  virtual ~Arg() = default;

 protected:
  std::string shortFlag;
  std::string longFlag;

  bool resolved = false;
};
