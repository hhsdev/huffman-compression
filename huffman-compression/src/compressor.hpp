#ifndef H_COMPRESSOR_COMPRESSOR_H_
#define H_COMPRESSOR_COMPRESSOR_H_
#include <array>
#include <climits>
#include <memory>
#include <string>

#include "./base_bitset.hpp"
#include "./dynamic_bitset.hpp"
#include "./util.hpp"

class Compressor {
 public:
  Compressor() = default;
  int getFrequency(const unsigned char ch) const;
  const BaseBitset& getCode(const unsigned char ch) const;

  void compress(const std::string& input);
  void countCharacterFrequencies(const std::string& input);

  DynamicBitset& getBits() { return compressedBits; }

 private:
  void loadCompressionCodes();

  DynamicBitset compressedBits;
  Huffman::CharSizedArray<int> characterFrequencies;
  Huffman::CharSizedArray<std::unique_ptr<BaseBitset>> compressionCodes;
};

#endif  //! H_COMPRESSOR_COMPRESSOR_H_
