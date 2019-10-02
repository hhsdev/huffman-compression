#include <climits>
#include <sstream>
#include <iostream>
#include "./compressor.hpp"
#include "./huffman_tree.hpp"

Compressor::Compressor() : characterFrequencies() {}

int Compressor::getFrequency(const char ch) const {
  return characterFrequencies[ch];
}

std::string Compressor::compress(const std::string& input) {
  countFrequencies(input);
  auto prefixes = HuffmanTree(characterFrequencies).buildPrefixArray();
  Huffman::Word buffer = 0;
  int codeBitsInBuffer = 0;
  std::string ret;
  std::ostringstream os(ret);

  for (const char ch : input) {
    const auto& prefix = prefixes[ch];
    bool spillOver = packIntoBuffer(buffer, codeBitsInBuffer, prefix.getCode(),
                                    prefix.getCodeLength());
    if (spillOver) {
      os << buffer;
      auto [spilledBits, spilledBitsSize] = getSpilledBits(
          prefix.getCode(), prefix.getCodeLength(), codeBitsInBuffer);
      buffer = 0;
      codeBitsInBuffer = 0;
      packIntoBuffer(buffer, codeBitsInBuffer, spilledBits, spilledBitsSize);
    }
  }
  os << buffer;
  return ret;
}

void Compressor::countFrequencies(const std::string& input) {
  for (char c : input) {
    characterFrequencies[c] += 1;
  }
}
bool Compressor::packIntoBuffer(Huffman::Word& buffer, int& codeBitsInBuffer, int code,
                                int codeLength) {
  constexpr int bufferSize = sizeof(buffer) * CHAR_BIT;
  const int bitsToAdd = std::min(bufferSize - codeBitsInBuffer, codeLength);
  buffer <<= bitsToAdd;
  buffer |= (code >> (codeLength - bitsToAdd));
  codeBitsInBuffer += bitsToAdd;
  return codeBitsInBuffer > bufferSize;
}

std::pair<int, int> Compressor::getSpilledBits(int code, int codeLength,
                                               int codeBitsInBuffer) {
  std::pair<int, int> ret;
  constexpr int bufferSize = sizeof(code) * CHAR_BIT;
  int spilledBitsSize = codeBitsInBuffer - bufferSize;
  int spilledBits = code & ((1L << spilledBitsSize) - 1);
  ret.first = spilledBits;
  ret.second = spilledBitsSize;
  return ret;
}
