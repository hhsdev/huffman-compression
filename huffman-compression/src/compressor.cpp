#include <climits>
#include <sstream>

#include "./compressor.hpp"
#include "./code_word.hpp"
#include "./compression_codes_builder.hpp"
#include "./huffman_node.hpp"
#include "./huffman_tree.hpp"

std::string to_binary(const CodeWord& code) {
  int length = code.length();
  std::string toReturn;
  unsigned int mask = 1;
  for (int i = length - 1; i >= 0; --i) {
    if ((code.getCode() >> i) & mask == 1) {
      toReturn += "1";
    } else {
      toReturn += "0";
    }
  }
  return toReturn;
}
Compressor::Compressor() : characterFrequencies() {}

int Compressor::getFrequency(const char ch) const {
  return characterFrequencies[ch];
}

BitBuffer Compressor::compress(const std::string& input) {
  countCharacterFrequencies(input);
  CompressionCodesBuilder<HuffmanTree> codeBuilder;
  compressionCodes = codeBuilder.buildFrom(HuffmanTree(characterFrequencies));
  BitBuffer buffer;

  for (const char ch : input) {
    const auto& code = compressionCodes[ch];
    buffer.append(code.getCode(), code.length());
  }
  return buffer;
}

void Compressor::countCharacterFrequencies(const std::string& input) {
  characterFrequencies = {};
  for (char c : input) {
    characterFrequencies[c] += 1;
  }
}
