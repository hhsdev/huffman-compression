#pragma once
#include <climits>
#include <array>

namespace Huffman {
  constexpr int NUM_ALL_CHARS = UCHAR_MAX + 1;
  template <typename T>
  using CharSizedArray = std::array<T, NUM_ALL_CHARS>;
}
