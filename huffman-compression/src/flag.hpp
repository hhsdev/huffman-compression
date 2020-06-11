#pragma once
#include <string>
#include "./arg.hpp"

class Flag : public Arg {
 public:
  Flag(const std::string& shortFlag, const std::string& longFlag,
       const bool defaultValue = false);

  void set(bool newValue);
  operator bool();
   
  void process(int index, int argc, char** argv) override;
  void xorProcess() override;
 private:
  bool value;
};
