#include "catch.hpp"
#include "bitset_32.hpp"

TEST_CASE("Bitset32", "[Bitset32]") {
  Bitset32 b;
  b.push_back(1);
  REQUIRE(b.size() == 1);
  REQUIRE(b.toString() == "1");

  b.push_back(0);
  b.push_back(1);
  REQUIRE(b.toString() == "101");
  REQUIRE(b.size() == 3);
  
  b.push_back(0);
  REQUIRE(b[3] == 1);
  REQUIRE(b[2] == 0);
  REQUIRE(b[1] == 1);
  REQUIRE(b[0] == 0);

  b[3] = 0;
  REQUIRE(b[3] == 0);
  REQUIRE(b[3].flip() == 1);
  REQUIRE(b[3] == 1);

  REQUIRE(b.getByte(0) == 0b0000'1010);
}
