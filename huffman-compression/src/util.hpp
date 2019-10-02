#pragma once
#include <climits>

namespace Huffman {
  using Word = int;
  constexpr int NUM_ALL_CHARS = UCHAR_MAX + 1;
  template <typename T>
  using CharSizedArray = std::array<T, NUM_ALL_CHARS>;
}
