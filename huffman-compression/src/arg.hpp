#pragma once

class Arg {
 public:
  Arg() = default;
  virtual bool canProcess(const std::string& flag) const = 0;
  virtual void process(int index, int argc, char** argv) = 0;
  virtual void xorProcess(int index, int argc, char** argv) = 0;
  virtual bool isDoneProcessing() const = 0;
  virtual ~Arg() = default;
};
