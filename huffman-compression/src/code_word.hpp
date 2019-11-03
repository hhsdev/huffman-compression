#pragma once
#include <string>
class Prefix {
 public:
  Prefix() : code(0), codeLength(0) {}
  Prefix(int code, int codeLength) : code(code), codeLength(codeLength) {}
  void add(bool i) {
    code <<= 1;
    code |= i;
    ++codeLength;
  }
  int getCode() const { return code; }
  int getCodeLength() const { return codeLength; }
  std::string toString() {
    std::string ret;
    for (int n = codeLength - 1; n >= 0; --n) {
      int nthBit = (code >> n) & 1;
      ret += (nthBit ? "1" : "0");
    }
    return ret;
  }

 private:
  int code;
  int codeLength;
};
