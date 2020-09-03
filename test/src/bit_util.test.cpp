#include "catch.hpp"
#include "bit_util.hpp"

TEST_CASE("Bit twiddling utilities", "[BitUtil]") {
  using namespace BitUtil;
  auto [front, back] = split(0b1111'1010, 4);
  REQUIRE(front == 0b1111);
  REQUIRE(back == 0b1010);

  REQUIRE(nthBit(0b1011, 2) == 0);
  REQUIRE(nthBit(0b1011, 1) == 1); 
}

TEST_CASE("Bit offsets are correctly calculated", "[BitUtil]") {
  using namespace BitUtil;

  REQUIRE(bitOffset(0) == 0);
  REQUIRE(bitOffset(1) == 1);
  REQUIRE(bitOffset(8) == 0);
  REQUIRE(bitOffset(9) == 1);
  REQUIRE(bitOffset(12) == 4);
}

TEST_CASE("Byte indices are correctly calculated", "[BitUtil]") {
  using namespace BitUtil;

  REQUIRE(toByteIndex(0) == 0);
  REQUIRE(toByteIndex(1) == 0);
  REQUIRE(toByteIndex(8) == 1);
  REQUIRE(toByteIndex(9) == 1);
  REQUIRE(toByteIndex(12) == 1);
}

TEST_CASE("Byte sizes are correctly calculated", "[BitUtil]") {
  using namespace BitUtil;

  REQUIRE(toByteSize(0) == 0);
  REQUIRE(toByteSize(1) == 1);
  REQUIRE(toByteSize(8) == 1);
  REQUIRE(toByteSize(9) == 2);
  REQUIRE(toByteSize(12) == 2);
}
