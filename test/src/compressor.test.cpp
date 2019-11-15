#include <bitset>
#include <iostream>
#include <limits>
#include <string>
#include "catch.hpp"
#include "compressor.hpp"

std::string bitRepresentation(const std::string& input) {
  std::string ret;
  for (char ch : input) {
    std::string byte;
    std::bitset<CHAR_BIT> bits_lookup(ch);
    for (int i = CHAR_BIT - 1; i >= 0; --i) {
      if (bits_lookup[i]) {
        byte += "1";
      } else {
        byte += "0";
      }
    }
    ret += byte;
  }
  return ret;
}

TEST_CASE("Compressor", "[Compressor]") {
  std::string testString = "aabbbccdcce    ee e\ne";
  Compressor c;
  SECTION("Character frequencies are counted") {
    c.countCharacterFrequencies(testString);
    REQUIRE(c.getFrequency('a') == 2);
    REQUIRE(c.getFrequency('b') == 3);
    REQUIRE(c.getFrequency('c') == 4);
    REQUIRE(c.getFrequency('d') == 1);
    REQUIRE(c.getFrequency('e') == 5);
  }
  
  SECTION("Counts of unoccurring chars are set to 0") {
    c.countCharacterFrequencies(testString);
    REQUIRE(c.getFrequency(0) == 0);
    REQUIRE(c.getFrequency('f') == 0);
    REQUIRE(c.getFrequency(CHAR_MAX) == 0);
  }

  SECTION("Get individual codes") {
	c.buildCodeTable(testString);
    c.compress(testString);
    // occurred characters' code size will be greater than 0
    REQUIRE(c.getCode(testString[0]).size() > 0);
    // whereas unoccurred characters' will be 0
    REQUIRE(c.getCode('f').size() == 0);
  }
  SECTION("Compression") {
    // fixtures taken from https://www.techiedelight.com/huffman-coding/
    const std::string inputFixture =
        "Huffman coding is a data compression algorithm.";
    const std::string outputFixture =
        "0000100000111101111010000101011011001111000010111010110001011111010010"
        "1101001100100101101101001100111100100010100101011101011001100111101100"
        "101101101011010000011100101011110110111111101000111111";

	c.buildCodeTable(inputFixture);
    c.compress(inputFixture);
    // since huffman encoding is optimal, the size of compressed output
    // should be the same, even if encodings are different
    REQUIRE(c.getBits().size() == outputFixture.size());
  }
  SECTION("Converting to canonical format") {
	Huffman::CharSizedArray<uint32_t> frequencies = { 0 };
	frequencies['b'] = 6;
	frequencies['a'] = 3;
	frequencies['c'] = 1;
	frequencies['d'] = 1;
	c.buildCodeTable(frequencies);

	REQUIRE(c.getCode('b').toString() == "0");
	REQUIRE(c.getCode('a').toString() == "10");
	REQUIRE(c.getCode('c').toString() == "110");
	REQUIRE(c.getCode('d').toString() == "111");
  }
}
