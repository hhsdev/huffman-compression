#include <climits>
#include <sstream>

#include "./compression_codes_builder.hpp"
#include "./compressor.hpp"
#include "./huffman_node.hpp"
#include "./huffman_tree.hpp"

int Compressor::getFrequency(const unsigned char ch) const {
  return characterFrequencies[ch];
}

const BaseBitset& Compressor::getCode(const unsigned char ch) const {
  return *compressionCodes[ch];
}
void Compressor::compress(const std::string& input) {
  countCharacterFrequencies(input);
  loadCompressionCodes();

  for (const char ch : input) {
    const auto& code = *compressionCodes[ch];
    // TODO: Replace this with dynamic bitset
    uint32_t bits = 0;
    for (int i = code.size() - 1; i >= 0; --i) {
      compressedBits.push_back(code[i]);
    }
  }
}

void Compressor::countCharacterFrequencies(const std::string& input) {
  characterFrequencies = {};
  for (char c : input) {
    characterFrequencies[c] += 1;
  }
}

void Compressor::loadCompressionCodes() {
  CompressionCodesBuilder<HuffmanTree> codeBuilder;
  const auto& codes = codeBuilder.buildFrom(HuffmanTree(characterFrequencies));
  // since codes from builder are held in unique_ptrs
  // we need to clone them
  for (int i = 0; i < compressionCodes.size(); ++i) {
    compressionCodes[i].reset(codes[i] ? codes[i]->clone() : new Bitset32());
  }
}
