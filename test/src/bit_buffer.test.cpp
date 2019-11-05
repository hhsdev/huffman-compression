#include "./bit_buffer.hpp"
#include "catch.hpp"

TEST_CASE("Bit buffer", "[BitBuffer]") {
  using container_type = BitBuffer::container_type;
  BitBuffer buffer;
  SECTION("getting i-th byte") {
    unsigned int fixture = 0b1111'1111'1010'1010'0000'0000'0101'0101;
    REQUIRE(BitBuffer::nthByte(fixture, 0) == 0b0101'0101);
    REQUIRE(BitBuffer::nthByte(fixture, 1) == 0b0000'0000);
    REQUIRE(BitBuffer::nthByte(fixture, 2) == 0b1010'1010);
    REQUIRE(BitBuffer::nthByte(fixture, 3) == 0b1111'1111);
  }
  SECTION("Splitting bits") {
    auto [a, b] = BitBuffer::split(0b1111'1111'1111'1111, 16, 4);
    REQUIRE(a == 0b1111);
    REQUIRE(b == 0b1111'1111'1111);
  }
  SECTION("Adding bits") {
    buffer.append(0b1111'1111, 8);
    REQUIRE(int(buffer.getData()[0]) == 0b1111'1111);
    REQUIRE(buffer.getLength() == 8);
    REQUIRE(buffer.getFreeSpace() == 0);

    buffer.append(1, 1);
    REQUIRE(buffer.getData().size() == 2);
    REQUIRE(int(buffer.getData()[0]) == 0b1111'1111);
    REQUIRE(int(buffer.getData()[1]) == 0b1000'0000);
    REQUIRE(buffer.getLength() == 9);
    REQUIRE(buffer.getFreeSpace() == 7);

    buffer.append(0b1010'0001'001, 11);
    REQUIRE(buffer.getData().size() == 3);
    REQUIRE(buffer.getData() == std::vector<unsigned char>({0b1111'1111, 0b1101'0000, 0b1001'0000}));
    REQUIRE(buffer.getLength() == 20);
    REQUIRE(buffer.getFreeSpace() == 4);
  }
}
