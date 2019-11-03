#include "./code_word.hpp"


std::ostream& operator<<(std::ostream& os, const CodeWord& word) {
  int wordSizeInBytes = sizeof(CodeWord::code_t);
  CodeWord::code_t code = word.getCode();
  int byteMask = 0b1111'1111;
  for (int i = wordSizeInBytes - 1; i >= 0; --i) {
	const unsigned char ithByte = (code >> (i * 8)) & byteMask;
	os << ithByte;
  }
  return os;
}

std::pair<CodeWord, CodeWord> CodeWord::split(const CodeWord& word, int frontPartLength) {
  const CodeWord::code_t wholeCode = word.getCode();
  const int backPartLength = word.length() - frontPartLength;
  // left shift out the back part
  const CodeWord::code_t frontPart = wholeCode >> backPartLength;

  // 0b11...1 (backPartLength times)
  const CodeWord::code_t mask = (1L << backPartLength) - 1; 
  // mask out the front part of code
  const CodeWord::code_t backPart = wholeCode & mask;

  return {CodeWord(frontPart, frontPartLength), CodeWord(backPart, backPartLength)};
}
