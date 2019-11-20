#pragma once
#include <iostream>
#include <string_view>

#include "./decompressor.hpp"
#include "./string_view_bitset.hpp"
#include "./tree_reconstruction.hpp"
#include "./util.hpp"

class Reader {
  static const std::string headMagicBytes;
  static const std::string bodyMagicBytes;

 public:
  Reader() = default;
  void write(std::ostream& output) {}

  std::string decompress(std::istream& source) {
    std::string buffer = getContents(source);
    if (!isCorrectType(buffer)) throw std::runtime_error("Wrong file type");

    Huffman::CharSizedArray<unsigned char> codeLengths = extractHead(buffer);
    HuffmanTree tree = TreeReconstruction::reconstructFrom(codeLengths);
    return decompressor.decompress(tree, extractData(buffer));
  }

  // private:
  Huffman::CharSizedArray<unsigned char> extractHead(
      const std::string& contents) {
    Huffman::CharSizedArray<unsigned char> ret;
    const int offset = headMagicBytes.size();
    for (int i = offset, ch = 0; i < Huffman::NUM_ALL_CHARS + offset;
         ++i, ++ch) {
      int chLength = contents[i];
      ret[ch] = chLength;
    }
    return ret;
  }

  StringViewBitset extractData(const std::string& contents) {
    const int paddingByteSize = 1;
    const int paddingByteLocation =
        headMagicBytes.size() + Huffman::NUM_ALL_CHARS + bodyMagicBytes.size() + 4;
    const int padding = contents[paddingByteLocation];
    std::string_view view = contents;
    view = view.substr(paddingByteLocation + 1);
    return StringViewBitset(view, view.size() * CHAR_BIT - padding);
  }

  bool isCorrectType(const std::string& contents) {
    return contents.substr(0, 4) == headMagicBytes;
  }

  std::string getContents(std::istream& source) {
    std::ostringstream sstr;
    sstr << source.rdbuf();
    return sstr.str();
  }

  Decompressor decompressor;
};

