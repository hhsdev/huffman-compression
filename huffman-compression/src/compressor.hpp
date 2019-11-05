#ifndef H_COMPRESSOR_COMPRESSOR_H_
#define H_COMPRESSOR_COMPRESSOR_H_
#include <array>
#include <climits>
#include <string>

#include "./util.hpp"
#include "./code_word.hpp"
#include "./bit_buffer.hpp"

class Compressor {
 public:
  Compressor();
  BitBuffer compress(const std::string& input);
  void countCharacterFrequencies(const std::string& input);
  int getFrequency(const char ch) const;
 private:
  Huffman::CharSizedArray<int> characterFrequencies;
  Huffman::CharSizedArray<CodeWord> compressionCodes;
};

#endif  //! H_COMPRESSOR_COMPRESSOR_H_
