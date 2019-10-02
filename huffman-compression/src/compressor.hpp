#ifndef H_COMPRESSOR_COMPRESSOR_H_
#define H_COMPRESSOR_COMPRESSOR_H_
#include <array>
#include <climits>
#include <string>
#include "./util.hpp"
class Compressor {
 public:
  Compressor();
  std::string compress(const std::string& input);
  void countFrequencies(const std::string& input);
  int getFrequency(const char ch) const;

  bool packIntoBuffer(Huffman::Word& buffer, int& codeBitsInBuffer,
	                  int code, int codeLength);
  std::pair<int, int> getSpilledBits(int code, int codeLength,
                                     int codeBitsInBuffer);
 private:
  Huffman::CharSizedArray<int> characterFrequencies;
};

#endif  //! H_COMPRESSOR_COMPRESSOR_H_

