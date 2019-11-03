#pragma once
#include <string>
#include <iostream>
#include "util.hpp"

class CodeWord {
 public:
  using code_t = unsigned int;
  static constexpr int CODE_MAX = sizeof(code_t) * CHAR_BIT;
  friend std::ostream& operator<<(std::ostream& os, const CodeWord& word);
  static std::pair<CodeWord, CodeWord> split(const CodeWord& word, int firstCodeWordLength);

  CodeWord() : code(0), codeLength(0) {}
  CodeWord(code_t code, int codeLength) : CodeWord() {
	this->code = code & ((1L<<codeLength)-1);
	this->codeLength = codeLength;
  }

  void add(int code, int codeLength) {
    this->code <<= codeLength;
    this->code |= code;
	this->codeLength += codeLength;
  }
  
  bool willFit(const CodeWord& word) {
	return word.length() + this->length() <= CODE_MAX;
  }

  int freeSpace() {
	return CODE_MAX - codeLength;
  }
  int getCode() const { return code; }

  int length() const { return codeLength; }
  std::string toBitString() const {
    std::string ret;
    for (int n = codeLength - 1; n >= 0; --n) {
      int nthBit = (code >> n) & 1;
      ret += (nthBit ? "1" : "0");
    }
    return ret;
  }

  CodeWord operator+(const CodeWord& other) const {
	CodeWord ret(*this);
	ret.add(other.getCode(), other.length());
	return ret;
  }

  CodeWord& operator+=(const CodeWord& other) {
	this->add(other.getCode(), other.length());
	return *this;
  }

  void clear() {
	code = 0;
	codeLength = 0;
  }
 private:
  int code;
  int codeLength;
};

std::ostream& operator<<(std::ostream& os, const CodeWord& word);
