#include "./bitset_32.test.hpp"

TEST_CASE("Default constructed Bitset32 has sane defaults") {
  Bitset32 bits;

  assertDataAndSizeEquals(bits, "");
}

TEST_CASE("Pushing back bits works as intended", "[Bitset32]") {
  Bitset32 bits;
  repeatedlyCallPushBack(bits, "101010");
  
  assertDataAndSizeEquals(bits, "101010");
}

TEST_CASE("Incrementing bitset works as intended", "[Bitset32]") {
  Bitset32 bits;
  
  repeatedlyCallPushBack(bits, "00");
  ++bits;
  assertDataAndSizeEquals(bits, "01");
  ++bits;
  ++bits;
  assertDataAndSizeEquals(bits, "11");
  ++bits;
  assertDataAndSizeEquals(bits, "00");
}

TEST_CASE("Incrementing empty bitset does not increase", "[Bitset32]") {
  Bitset32 empty;
  ++empty;
  assertDataAndSizeEquals(empty, "");
}

TEST_CASE("Operator[] works as intended") {
  Bitset32 bits;
  repeatedlyCallPushBack(bits, "101010");

  assertEqualWithBrackets(bits, "101010");
}

TEST_CASE("Operator[] assignment works as intended") {
  Bitset32 bits;
  repeatedlyCallPushBack(bits, "101010");

  bits[1] = 0;
  bits[3] = 0;
  bits[5] = 0;

  assertEqualWithBrackets(bits, "000000");
}

TEST_CASE("getByte returns correct byte") {
  Bitset32 bits;
  repeatedlyCallPushBack(bits, "11110000");

  REQUIRE(bits.getByte(0) == 0b1111'0000);
}

TEST_CASE("clear works correctly") {
  Bitset32 bits;
  repeatedlyCallPushBack(bits, "11110000");

  bits.clear();

  assertDataAndSizeEquals(bits, "");
}
