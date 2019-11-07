#ifndef H_COMPRESSOR_COMPRESSOR_H_
#define H_COMPRESSOR_COMPRESSOR_H_
#include <array>
#include <memory>
#include <climits>
#include <string>

#include "./util.hpp"
#include "./base_bitset.hpp"
#include "./bit_buffer.hpp"

class Compressor {
 public:
  Compressor();
  int getFrequency(const char ch) const;

  BitBuffer compress(const std::string& input);
  void countCharacterFrequencies(const std::string& input);
  void loadCompressionCodes();
 private:
  Huffman::CharSizedArray<int> characterFrequencies;
  Huffman::CharSizedArray<std::unique_ptr<BaseBitset>> compressionCodes;
};

#endif  //! H_COMPRESSOR_COMPRESSOR_H_
