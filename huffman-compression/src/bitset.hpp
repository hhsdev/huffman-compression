#pragma once

#include <string_view>
#include <climits>
#include <cmath>

class Bitset {
public:
  Bitset(std::string_view view, int numBits)
    : mView(view), mBitSize(numBits) {}
  
  uint8_t getByte(const int index) const {
    return mView[index];
  }

  int size() const { return mBitSize; }

  bool operator[](const int index) const {
    const int byteIndex = index / CHAR_BIT;
    const int bitOffset = index % CHAR_BIT;
    // Unlike arrays, bitset indices starts from the right, i.e.:
    // 0x0000000000000000
    //   ^15            ^0
    return mView[mView.size() - byteIndex - 1] >> bitOffset & 1U;
  }
private:
  std::string_view mView;
  int mBitSize;
};
