#pragma once
#include <algorithm>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "./compressor.hpp"
#include "./util.hpp"

class MetaData {
 public:
  std::string createMetaData(const Compressor& compressor) {
    std::string ret;
    ret += "HEAD";
    for (int i = 0; i < Huffman::NUM_ALL_CHARS; ++i) {
      const auto& code = compressor.getCode(i);
      ret.push_back((unsigned char)code.size());
    }
    return ret;
  }

  std::vector<std::pair<unsigned char, int>> createArray(
      const std::string& contents) {
    std::vector<std::pair<unsigned char, int>> ret;
    verifyFormat(contents);
    for (int i = 0; i < Huffman::NUM_ALL_CHARS; ++i) {
      if (contents[i] > 0) {
        ret.push_back({i, contents[i]});
      }
    }
    std::stable_sort(
        ret.begin(), ret.end(),
        [](const std::pair<unsigned char, int>& a,
           const std::pair<unsigned char, int>& b) { return a.second < b.second; });
    return ret;
  }

  void verifyFormat(const std::string& contents) {
	if (contents.substr(0, 4) != "HEAD")
	  throw std::runtime_error("Unregconized compressed file format");
  }

};
