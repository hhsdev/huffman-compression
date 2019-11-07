#pragma once
#include <climits>
#include <utility>
#include <type_traits>

namespace BitUtil {


std::pair<unsigned char, unsigned char> split(unsigned char byte,
                                              int frontBitsLength);
template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type nthBit(
    T num, int index) {
  return (num >> index) & 1U;
}

}
