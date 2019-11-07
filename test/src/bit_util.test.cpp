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
