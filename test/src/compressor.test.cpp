#include <limits>
#include <string>
#include <bitset>
#include "catch.hpp"
#include "compressor.hpp"


std::string bitRepresentation(const std::string& input) {
  std::string ret;
  for (char ch : input) {
	std::string byte;
	std::bitset<CHAR_BIT> bits_lookup(ch);
	for (int i = CHAR_BIT - 1; i >= 0; --i) {
	  if(bits_lookup[i]) {
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

  SECTION("Compression") {
	// fixtures taken from https://www.techiedelight.com/huffman-coding/
	const std::string inputFixture = "Huffman coding is a data compression algorithm."; 
	const std::string outputFixture = "00001000001111011110100001010110110011110000101110101100010111110100101101001100100101101101001100111100100010100101011101011001100111101100101101101011010000011100101011110110111111101000111111";


	auto output = c.compress(inputFixture);
	// since huffman encoding is optimal, the size of compressed strings
	// should be the same, even if encoding is different
	REQUIRE(output.getLength() == outputFixture.size());
  }
}
