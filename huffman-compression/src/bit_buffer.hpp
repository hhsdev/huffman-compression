#pragma once
#include <climits>
#include <cmath>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

template <typename ToTest, typename Actual>
using if_integer_then_return =
    typename std::enable_if<std::is_integral<ToTest>::value, Actual>::type;
// This class makes it easier to work with arbitrary amount of bit data.
class BitBuffer {
 public:
  using size_type = unsigned long;
  using byte_type = unsigned char;
  using container_type = std::vector<byte_type>;
  template <typename T>
  static if_integer_then_return<T, byte_type> nthByte(T number, int i);

  template <typename T>
  static if_integer_then_return<T, std::pair<T, T>> split(T bits,
                                                          int wholeLength,
                                                          int frontPartLength);

  BitBuffer() : container(), freeSpace(0), bitsLength(0) {}


  template <typename T>
  if_integer_then_return<T, void> append(T bitData, int numBits);

  container_type& getData() { return container; };
  const container_type& getData() const { return container; };
  size_type getLength() const { return bitsLength; }
  size_type getFreeSpace() const { return freeSpace; }

 private:
  template <typename T>
  if_integer_then_return<T, void> packIntoExistingByte(T bitData, int numBits);
  container_type container;
  size_type freeSpace;
  size_type bitsLength;
};

template <typename T>
if_integer_then_return<T, void> BitBuffer::append(T bitData, int numBits) {
  if (numBits <= freeSpace) {
    packIntoExistingByte(bitData, numBits);
    freeSpace -= numBits;
  } else {
    auto [bitsThatFit, remainingBits] = split(bitData, numBits, freeSpace);

    packIntoExistingByte(bitsThatFit, freeSpace);

    const int lengthOfTInBits = sizeof(T) * CHAR_BIT;
    const int remainingBitsLength = numBits - freeSpace;
    // we left-shift 0b{n bits of 0s}{m bits of code} into
    // 0b{m bits of code}{n bits of 0s}, where n + m = length of T in bits
    remainingBits <<= (lengthOfTInBits - remainingBitsLength);
	
    const int remainingBitsLengthInBytes =
        std::ceil(remainingBitsLength / double(CHAR_BIT));
	// then we take from 0b{m bits of code}.. 1 byte at a time
	// (MSB first) and push them into the container
    for (int i = 0; i < remainingBitsLengthInBytes; ++i) {
      int n = sizeof(T) - 1 - i;
      byte_type byte = nthByte(remainingBits, n);
      container.push_back(byte);
    }
    if (remainingBitsLength % CHAR_BIT == 0) {
      freeSpace = 0;
    } else {
      freeSpace = CHAR_BIT - (remainingBitsLength % CHAR_BIT);
    }
  }
  bitsLength += numBits;
}

template <typename T>
if_integer_then_return<T, std::pair<T, T>> BitBuffer::split(
    T bits, int wholeLength, int frontPartLength) {
  const T backPartLength = wholeLength - frontPartLength;
  const T frontPart = bits >> backPartLength;
  const T mask = (1UL << backPartLength) - 1;
  const T backPart = bits & mask;

  return {frontPart, backPart};
}

template <typename T>
if_integer_then_return<T, unsigned char> BitBuffer::nthByte(T number, int i) {
  byte_type mask = 0b1111'1111;
  return (number >> (i * CHAR_BIT)) & mask;
}

template <typename T>
if_integer_then_return<T, void> BitBuffer::packIntoExistingByte(T bitData,
                                                                int numBits) {
  if (container.empty() || freeSpace < numBits) return;
  container.back() |= (bitData << (freeSpace - numBits));
}
