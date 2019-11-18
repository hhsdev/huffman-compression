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
