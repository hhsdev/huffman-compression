#include <climits>
#include <sstream>

#include "./compressor.hpp"
#include "./compression_codes_builder.hpp"
#include "./huffman_node.hpp"
#include "./huffman_tree.hpp"

Compressor::Compressor() : characterFrequencies() {}

int Compressor::getFrequency(const char ch) const {
  return characterFrequencies[ch];
}

BitBuffer Compressor::compress(const std::string& input) {
  countCharacterFrequencies(input);
  loadCompressionCodes();
  BitBuffer buffer;

  for (const char ch : input) {
    const auto& code = *compressionCodes[ch];
	// TODO: Replace this with dynamic bitset
	uint32_t bits = 0;
	for (int i = code.size() - 1; i >= 0; --i) {
	  bits <<= 1;
	  bits |= code[i];
	}
    buffer.append(bits, code.size());
  }
  return buffer;
}

void Compressor::countCharacterFrequencies(const std::string& input) {
  characterFrequencies = {};
  for (char c : input) {
    characterFrequencies[c] += 1;
  }
}

void Compressor::loadCompressionCodes() {
  CompressionCodesBuilder<HuffmanTree> codeBuilder;
  const auto& ref = codeBuilder.buildFrom(HuffmanTree(characterFrequencies));
  for (int i = 0; i < compressionCodes.size(); ++i) {
	compressionCodes[i].reset(ref[i] ? ref[i]->clone() : nullptr);
  }
}
