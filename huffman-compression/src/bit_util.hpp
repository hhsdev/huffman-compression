#pragma once
#include <climits>
#include <type_traits>
#include <utility>

namespace BitUtil {

std::pair<unsigned char, unsigned char> split(unsigned char byte,
                                              int frontBitsLength);
template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type nthBit(
    T num, int index) {
  return (num >> index) & 1U;
}

int bitOffset(int bitIndex);
int toByteIndex(int bitIndex);
int toByteSize(int bitIndex);
}  // namespace BitUtil

namespace BitUtil {

inline std::pair<unsigned char, unsigned char> split(unsigned char byte,
                                                     int frontBitsLength) {
  const int backBitsLength = CHAR_BIT - frontBitsLength;
  const unsigned char frontPart = byte >> backBitsLength;
  // this makes a mask with value 0b111..backBitsLength times..11
  const unsigned char mask = (1 << backBitsLength) - 1;
  const unsigned char backPart = byte & mask;

  return {frontPart, backPart};
}

inline int bitOffset(int bitIndex) { return bitIndex % CHAR_BIT; }

inline int toByteIndex(int bitIndex) { return bitIndex / CHAR_BIT; }

inline int toByteSize(int bitSize) {
  return std::ceil(bitSize / (double)CHAR_BIT);
}
}  // namespace BitUtil
