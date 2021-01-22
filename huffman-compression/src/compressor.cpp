#include <climits>
#include <iostream>
#include <sstream>
#include <utility>

#include "./compression_codes_builder.hpp"
#include "./compressor.hpp"

int Compressor::getFrequency(const unsigned char ch) const {
  return characterFrequencies[ch];
}

const BaseBitset& Compressor::getCode(const unsigned char ch) const {
  return *codeTable[ch];
}

void Compressor::compress(const std::string& input) {
  for (const unsigned char ch : input) {
    const auto& code = *codeTable[ch];
    for (int i = code.size() - 1; i >= 0; --i) {
      compressedBits.push_back(code[i]);
    }
  }
}

void Compressor::countCharacterFrequencies(const std::string& input) {
  characterFrequencies = {0};
  for (unsigned char c : input) {
    characterFrequencies[c] += 1;
  }
}

void Compressor::buildCodeTable(const std::string& input) {
  countCharacterFrequencies(input);
  doBuildCodeTable();
}

void Compressor::buildCodeTable(
    const Huffman::CharSizedArray<uint32_t>& frequencies) {
  characterFrequencies = frequencies;
  doBuildCodeTable();
}

void Compressor::buildCodeTable(const HuffmanTree& tree) {
  doBuildCodeTable(tree);
}

void Compressor::doBuildCodeTable() {
  const HuffmanTree tree(characterFrequencies);
  doBuildCodeTable(tree);
}

void Compressor::doBuildCodeTable(const HuffmanTree& tree) {
  CompressionCodesBuilder<HuffmanTree> builder;
  const auto& codes = builder.buildFrom(tree);
  // since codes from builder are held in unique_ptrs
  // we need to clone them
  for (int i = 0; i < codeTable.size(); ++i) {
    codeTable[i].reset(codes[i] ? codes[i]->clone() : new StaticBitset<>());
  }
  convertToCanonical();
}

void Compressor::convertToCanonical() {
  std::vector<uint8_t> bytesPresentInInput;

  for (auto byte : indices(codeTable)) {
    if (codeTable.exists(byte))
      bytesPresentInInput.push_back(i);
  }
  // for (uint8_t byte = 0; byte < codeTable.size(); ++byte) {
  //  // if (codeTable[i] != nullptr && codeTable[i]->size() > 0) {
  //  // bytesPresentInInput.push_back(i);
  //}

  auto sizewise_then_valuewise = [this](uint8_t a, uint8_t b) -> bool {
    if (codeTable[a]->size() < codeTable[b]->size())
      return true;
    else if (codeTable[a]->size() > codeTable[b]->size())
      return false;
    return (a < b ? true : false);
  };

  std::sort(bytesPresentInInput.begin(),
            bytesPresentInInput.end(),
            sizewise_then_valuewise);

  bool first = true;

  DynamicBitset<> previous;
  for (uint8_t b : bytesPresentInInput) {
    auto& current = *codeTable[b];
    if (first) {
      for (int i = 0; i < current.size(); ++i) {
        current[i] = 0;
      }
      first = false;
    } else {
      ++previous;
      if (current.size() == previous.size()) {
        // current.copy(previous);
        current.assign(previous);
      } else {
        int currentSize = current.size();
        current.assign(previous);
        if (current.size() > currentSize) {
          std::cout << "Something is wrong" << std::endl;
        }
        while (current.size() != currentSize) {
          current.push_back(0);
        }
      }
    }
    previous.assign(current);
  }
}
