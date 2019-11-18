#ifndef H_COMPRESSOR_COMPRESSOR_H_
#define H_COMPRESSOR_COMPRESSOR_H_
#include <array>
#include <climits>
#include <memory>
#include <string>

#include "./base_bitset.hpp"
#include "./dynamic_bitset.hpp"
#include "./huffman_tree.hpp"
#include "./util.hpp"

class HuffmanTree;

class Compressor {
 public:
  Compressor() = default;
  int getFrequency(const unsigned char ch) const;
  const BaseBitset& getCode(const unsigned char ch) const;

  void compress(const std::string& input);

  DynamicBitset<>& getBits() { return compressedBits; }

  const Huffman::CharSizedArray<uint32_t>& getFrequencyArray() const {
    return characterFrequencies;
  }
  
  const Huffman::CharSizedArray<std::unique_ptr<BaseBitset>>&
	getCodeTable() const { return codeTable; }
  void buildCodeTable(const std::string& input);
  void buildCodeTable(const Huffman::CharSizedArray<uint32_t>& frequencies);
  void buildCodeTable(const HuffmanTree& tree);

  void countCharacterFrequencies(const std::string& input);
  void convertToCanonical();
 private:
  void doBuildCodeTable();
  void doBuildCodeTable(const HuffmanTree& tree);

  DynamicBitset<> compressedBits;
  Huffman::CharSizedArray<uint32_t> characterFrequencies;
  Huffman::CharSizedArray<std::unique_ptr<BaseBitset>> codeTable;
};

#endif  //! H_COMPRESSOR_COMPRESSOR_H_
