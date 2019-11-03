#include "catch.hpp"
#include "prefix.hpp"


TEST_CASE("Prefix", "[Prefix]") {
  Prefix p;
  p.add(1);
  p.add(0);
  SECTION("add works") {
	REQUIRE(p.getCode() == 0b10);
	REQUIRE(p.getCodeLength() == 2);
  }
  SECTION("toString works") {
	REQUIRE(p.toString() == "10");
  }
}
