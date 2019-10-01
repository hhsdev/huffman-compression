#ifndef H_COMPRESSOR_COMPRESSOR_H_
#define H_COMPRESSOR_COMPRESSOR_H_
#include <array>
#include <climits>
#include <string>

class Compressor {
 public:
  using Word = int;
  static constexpr int NUM_ALL_CHARS = UCHAR_MAX + 1;
  using ArrayFittingAllChars = std::array<int, NUM_ALL_CHARS>;

  Compressor();
  std::string compress(const std::string& input);
  void countFrequencies(const std::string& input);
  int getFrequency(const char ch) const;

  bool packIntoBuffer(Word& buffer, int& codeBitsInBuffer, int code,
                      int codeLength);
  std::pair<int, int> getSpilledBits(int code, int codeLength,
                                     int codeBitsInBuffer);
 private:
  ArrayFittingAllChars characterFrequencies;
};

#endif  //! H_COMPRESSOR_COMPRESSOR_H_

