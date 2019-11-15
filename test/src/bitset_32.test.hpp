#include "bitset_32.hpp"
#include "catch.hpp"

void assertDataAndSizeEquals(const Bitset32& bits,
                             const std::string& bitstring) {
  REQUIRE(bits.size() == bitstring.size());
  REQUIRE(bits.toString() == bitstring);
}

void repeatedlyCallPushBack(Bitset32& bits, const std::string& bitstring) {
  for (char c : bitstring) {
    if (c == '1')
      bits.push_back(1);
    else if (c == '0')
      bits.push_back(0);
  }
}

void assertEqualWithBrackets(Bitset32& bits,
                                     const std::string& bitstring) {
  int index = 0;
  for (auto rit = bitstring.rbegin(); rit != bitstring.rend(); ++rit) {
    REQUIRE(bits[index] == (*rit == '1' ? 1 : 0));
    ++index;
  }
}

