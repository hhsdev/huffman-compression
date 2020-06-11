#pragma once
#include <iostream>
#include <string_view>

#include "./decompressor.hpp"
#include "./string_view_bitset.hpp"
#include "./tree_reconstruction.hpp"
#include "./util.hpp"

/**
 * Reads a compressed a file and decompresses it.
 */
class Reader {
  static const std::string headMagicBytes;
  static const std::string bodyMagicBytes;

 public:
  Reader() = default;
  std::string decompress(std::istream& source);

 private:
  Huffman::CharSizedArray<unsigned char> extractHead(
      const std::string& contents);
  StringViewBitset extractData(const std::string& contents);
  bool isWellFormed(const std::string& contents);
  std::string getContents(std::istream& source);

  Decompressor mDecompressor;
};
