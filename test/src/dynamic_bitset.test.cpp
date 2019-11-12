#include "catch.hpp"
#include "./dynamic_bitset.hpp"

TEST_CASE("dynamic_bitset", "[DynamicBitset]") {
  DynamicBitset db;
  db.push_back(0);
  db.push_back(1);
  REQUIRE(db.size() == 2);
  REQUIRE(db.toString() == "01");

  db.push_back(0);
  db.push_back(1);
  db.push_back(1);
  REQUIRE(db.toString() == "01011");
  db[2] = 1;
  db[4] = 1;
  REQUIRE(db.toString() == "11111");
  REQUIRE(db.size() == 5);

  REQUIRE(db.getByte(0) == 0b0001'1111);
  auto newDb = db.clone();
  REQUIRE(newDb->toString() == "11111");

  delete newDb;
}
