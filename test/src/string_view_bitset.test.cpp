#include "./string_view_bitset.test.hpp"
#include "./bitset_common.test.hpp"

void setEveryBits(StringViewBitset& bits);
void unsetEveryBits(StringViewBitset& bits);

TEST_CASE("Pushing back works as intended", "[StringViewBitset]") {
  std::string testString = { 0b0011'1111, 0b0011'1111, 0b0011'1111};
  StringViewBitset bits(testString, 24);

  assertDataAndSizeEquals(bits, "001111110011111100111111");

  repeatedlyCallPushBack(bits, "01");

  assertDataAndSizeEquals(bits, "00111111001111110011111101");
  assertEqualWithBrackets(bits, "00111111001111110011111101");
  
  setEveryBits(bits);
  assertDataAndSizeEquals(bits, "11111111111111111111111111");
  assertEqualWithBrackets(bits, "11111111111111111111111111");

  unsetEveryBits(bits);
  assertDataAndSizeEquals(bits, "00000000000000000000000000");
  assertEqualWithBrackets(bits, "00000000000000000000000000");
}

TEST_CASE("Alternating access and pushing back works as intended",
          "[StringViewBitset]") {
  std::string testString = { 0b0000'0000, 0b0000'0000, 0b0000'0000};
  StringViewBitset bits(testString, 24);
  
  bits[0] = 1;
  assertDataAndSizeEquals(bits, "000000000000000000000001");
  repeatedlyCallPushBack(bits, "000");
  assertDataAndSizeEquals(bits, "000000000000000000000001000");
}

void setEveryBits(StringViewBitset& bits) {
  for (int i = 0; i < bits.size(); ++i) {
	bits[i] = 1;
  }
}

void unsetEveryBits(StringViewBitset& bits) {
  for (int i = 0; i < bits.size(); ++i) {
	bits[i] = 0;
  }
}
