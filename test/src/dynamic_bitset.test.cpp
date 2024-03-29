#include "./bitset_common.test.hpp"
#include "./dynamic_bitset.hpp"
#include "catch.hpp"

TEST_CASE("push_back works as intended", "[DynamicBitset]") {
  const std::vector<std::string> testStrings = {
      "0000100000111101111010000101011011001111000010111010110001011111010010"
      "1101001100100101101101001100111100100010100101011101011001100111101100"
      "101101101011010000011100101011110110111111101000111111",

      "0000000011111111000000001111111110000000111111110000000011111111"
      "0000000011111111000000001111111110000000111111110000000011111111"
      "0000000011111111000000001111111110000000111111110000000011111111"
      "0000000011111111000000001111111110000000111111110000000011111111",

      "10000000000000000000000000000000"
      "11000000000000000000000000000000"
      "11100000000000000000000000000000"
      "11110000000000000000000000000000"
      "11111000000000000000000000000000"
      "11111100000000000000000000000000"
      "11111110000000000000000000000000"
      "11111111000000000000000000000000"};

  for (const std::string& testString : testStrings) {
    DynamicBitset<> bits;
    repeatedlyCallPushBack(bits, testString);
    assertDataAndSizeEquals(bits, testString);
  }
}

TEST_CASE("Testing about getByte", "[DynamicBitset]") {
  //                       "10100000 11111111 00000000 01010101 10101010
  //                       00000000 11111111 01010101 10101010 000";
  std::string testString =
      "101 00001111 11111000 00000010 10101101 01010000 00000111 11111010 "
      "10101101 01010000";

  DynamicBitset<> bits;
  repeatedlyCallPushBack(bits, testString);
  REQUIRE(int(bits.getByte(0)) == 0b01010000);
  REQUIRE(int(bits.getByte(1)) == 0b10101101);
  REQUIRE(int(bits.getByte(2)) == 0b11111010);
  REQUIRE(int(bits.getByte(3)) == 0b00000111);
  REQUIRE(int(bits.getByte(4)) == 0b01010000);
  REQUIRE(int(bits.getByte(5)) == 0b10101101);
  REQUIRE(int(bits.getByte(6)) == 0b00000010);
  REQUIRE(int(bits.getByte(7)) == 0b11111000);
  REQUIRE(int(bits.getByte(8)) == 0b00001111);
  REQUIRE(int(bits.getByte(9)) == 0b00000101);
}

TEST_CASE("Outputting to a stream works correctly", "[DynamicBitset]") {
  //                           h          e        l       l       o
  std::string testString = "01101000 01100101 01101100 01101100 01101111";

  DynamicBitset<> bits;
  repeatedlyCallPushBack(bits, testString);
  std::ostringstream oss;
  oss << bits;
  REQUIRE(oss.str() == std::string("hello"));
}
